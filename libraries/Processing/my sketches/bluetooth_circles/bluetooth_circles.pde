/*Circle Dragger: Simple Android-Processing Sketch written by ScottC on 13/03/2013.
 Visit: http://arduinobasics.blogspot.com/
*/

int circleWidth = 150;

void setup(){
 orientation(LANDSCAPE);
}

void draw(){
 background(255,100,0);
 fill(0);
 ellipse(mouseX,mouseY,circleWidth,circleWidth);
}
