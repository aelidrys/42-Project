#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reconstructed structural layout based on stack alignment offsets
struct Message {
    char msg[140];       // Offsets 0 to 139
    char username[40];   // Offsets 140 to 179
    int len;             // Offset 180 (0xb4)
};

// Isolated utility function present in the binary symbols
void secret_backdoor() {
    char cmd_buf[128];
    
    fgets(cmd_buf, 128, stdin);
    system(cmd_buf);
}

void set_username(struct Message *m) {
    char input_buffer[128];
    memset(input_buffer, 0, 128); // Cleared via 'rep stos'
    
    puts(">: Enter your username");
    printf(">>: ");
    
    fgets(input_buffer, 128, stdin);
    
    // The vulnerable loop using an off-by-one constraint (i <= 40)
    int i = 0;
    for (i = 0; i <= 40 && input_buffer[i] != '\0'; i++) {
        m->username[i] = input_buffer[i];
    }
    
    printf(">: Welcome, %s", m->username);
}

void set_msg(struct Message *m) {
    char local_buffer[1024];
    memset(local_buffer, 0, 1024); // Cleared via 'rep stos'
    
    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    
    fgets(local_buffer, 1024, stdin);
    
    // Reads from struct offset 180 (0xb4)
    int copy_len = m->len; 
    
    // Moves input into the struct base using the size constraint
    strncpy(m->msg, local_buffer, copy_len);
}

void handle_msg() {
    struct Message msg_struct;
    
    // Clean target structural fields
    memset(&msg_struct.username, 0, 40);
    msg_struct.len = 140; // Hardcoded initial size bound (0x8c)
    
    set_username(&msg_struct);
    set_msg(&msg_struct);
    
    puts(">: Msg sent!");
}

int main() {
    puts(
        "--------------------------------------------\n"
        "|   ~Welcome to l33t-m$n ~    v1337        |\n"
        "--------------------------------------------"
    );
    
    handle_msg();
    return 0;
}


// 0x000055555555488c  secret_backdoor