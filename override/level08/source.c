#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


void log_wrapper(FILE *log_file, const char *msg, const char *filename) {
    char log_buf[256]; // Frame size 0x130 leaves ~256 bytes for this buffer (-0x110 to -0x8)
    
    // Copy the prefix message ("Starting backup of " / "Finished backup of ")
    strcpy(log_buf, msg);
    
    // Inline strlen() via 'repnz scas' to locate the end of log_buf
    size_t len = strlen(log_buf);
    size_t remaining_space = 254 - len;
    
    // CRITICAL VULNERABILITY: 
    // The filename parameter (argv[1]) is passed directly as the format string argument!
    snprintf(log_buf + len, remaining_space, filename);
    
    // Strip trailing newline characters
    // 0x400d4c: "\n"
    log_buf[strcspn(log_buf, "\n")] = '\0';
    
    // Write the compiled string out to the log file descriptor
    // 0x400d4e: "%s\n"
    fprintf(log_file, "%s\n", log_buf);
}


int main(int argc, char **argv) {
    FILE *log_file;
    FILE *src_file;
    char backup_path[100]; // Located at -0x70(%rbp)
    int backup_fd = -1;    // Located at -0x78(%rbp)
    char c = (char)0xff;   // Located at -0x71(%rbp), initialized to EOF/0xff

    // Enforce exactly one command-line argument
    if (argc != 2) {
        // 0x400d57: "Usage: %s <filename>\n"
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    // Open the master log file
    // 0x400d6d: "./backups/.log", 0x400d6b: "r"
    log_file = fopen("./backups/.log", "r");
    if (log_file == NULL) {
        // 0x400d7c: "ERROR: Failed to open %s\n"
        printf("ERROR: Failed to open ./backups/.log\n"); 
        exit(1);
    }

    // Log the start of the operation
    log_wrapper(log_file, "Starting back up: ", argv[1]);

    // Open the user-specified target file for reading
    src_file = fopen(argv[1], "r");
    if (src_file == NULL) {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(1);
    }

    // Construct the target backup path string
    strcpy(backup_path, "./backups/");
    
    // The compiler generated an inline strlen() using 'repnz scas' here
    // to compute: max_len = 99 - strlen(backup_path)
    size_t current_len = strlen(backup_path);
    size_t max_append = 99 - current_len;
    strncat(backup_path, argv[1], max_append);

    // Open/Create the backup destination file
    // Flags: 0xc1 = O_WRONLY | O_CREAT | O_EXCL
    // Mode: 0x1b0 = 0660 permissions (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)
    backup_fd = open(backup_path, 0xc1, 0x1b0);
    if (backup_fd < 0) {
        // 0x400db6: "ERROR: Failed to open %s\n"
        printf("ERROR: Failed to open %s\n", backup_path);
        exit(1);
    }
    // ./backups/backups/../backups/../backups/../backups/../backups/../backups/../backups/../backups/../././././.pass
    // Byte-by-byte copy loop
    while (1) {
        c = fgetc(src_file);
        if (c == (char)0xff) { // Checking against EOF
            break;
        }
        write(backup_fd, &c, 1);
    }

    // Log the completion of the operation
    // 0x400dd2: "Finished backup of "
    log_wrapper(log_file, "Finished back up ", argv[1]);

    // Cleanup resources
    fclose(src_file);
    close(backup_fd);

    return 0;
}

