export class Point {
    constructor(x, y) {
      this.x = x;
      this.y = y;
    }

    translate(vec) {
        this.x += vec[0];
        this.y += vec[1];
    }
}

export class Rectangle {
    constructor(p1, p2, p3, p4) {

        this.points = [p1, p2, p3, p4];      
    }

    move(vec) {
        this.points.forEach(point => point.translate(vec));
    }
    
    getPoint(i)
    {
        return this.points[i];
    }

        
    displayPoint()
    {
        return this.points[0];
    }

    clone() {
        const clonedPoints = this.points.map(point => new Point(point.x, point.y));

        return new Rectangle(clonedPoints[0], clonedPoints[1], clonedPoints[2], clonedPoints[3]);
    }

}