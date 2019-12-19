import processing.serial.*;
Serial port;
String mensaje = "ABCDEFGHRISJTUVWKL    ";
int colorFondo = color(255,255,255);

int nextline = 10;

void setup() {
      port = new Serial(this, Serial.list()[0], 9600);
      size(640, 360);
      noSmooth();
}
void draw() {
  while (port.available() > 0) {
      int rectX = 640-60,rectWidth = 50,rectY = 10,rectHeight = 50;
      background(102);
      
      fill(255,0,0);
      rect(10, 10, 50, 50);
      fill(0,255,0);
      rect(70, 10, 50, 50);
      fill(0,0,255);
      rect(130, 10, 50, 50);
      
      fill(255,255,255);
      rect(rectX, rectY, rectWidth, rectHeight);
      
      if(mousePressed){
        if (mouseX > rectX && mouseX < rectX +rectWidth && mouseY > rectY && mouseY < rectY +rectHeight)
          colorFondo= color(255,255,255);
        else
          colorFondo = get(mouseX, mouseY);
      }

    String inBuffer = port.readStringUntil(nextline);   
    if (inBuffer != null) {     
      grafico( split(inBuffer,',') );
    }
  }
} // end draw

void grafico(String[] valores){
      fill(colorFondo);
      rect(0, 100, width, height - 100);
        
      noStroke();
      textSize(12);
      fill(255);
      for (int x = 0; x < valores.length; x = x + 1) {  
        text(mensaje.substring(x,x+1), 10, 30); 

        rect (x*35+20, height-int(valores[x]),
        30, int(valores[x]));
      }
}
