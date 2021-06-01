byte NT[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F};
byte WT[8] = {0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00};
byte BR[8] = {0x1F,0x1F,0x03,0x03,0x03,0x03,0x1F,0x1F};
byte BL[8] = {0x1F,0x1F,0x18,0x18,0x18,0x18,0x1F,0x1F};
byte NG[8] = {0x1F,0x1F,0x18,0x18,0x18,0x18,0x18,0x18};
byte LG[8] = {0x1F,0x1F,0x03,0x03,0x03,0x03,0x03,0x03};
byte NL[8] = {0x18,0x18,0x18,0x18,0x18,0x18,0x1F,0x1F};
byte LL[8] = {0x03,0x03,0x03,0x03,0x03,0x03,0x1F,0x1F};


 void bignummer()
{
lcd.createChar(1,NT);
lcd.createChar(2,WT);
lcd.createChar(3,BR);
lcd.createChar(4,BL);
lcd.createChar(5,NG);
lcd.createChar(6,LG);
lcd.createChar(7,NL);
lcd.createChar(8,LL);
}

void custom0(int col)
{ // uses segments to build the number 0
  lcd.setCursor(col, 0); 
  lcd.write(5);  
  lcd.write(6); 
  lcd.setCursor(col, 1);  
  lcd.write(7);  
  lcd.write(8);
}

void custom1(int col)
{
  lcd.setCursor(col,0);
  lcd.write(6);
  lcd.write(32);
  lcd.setCursor(col,1);
  lcd.write(8);
  lcd.write(1);
}

void custom2(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.setCursor(col, 1);
  lcd.write(4);
  lcd.write(1);
}

void custom3(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(6);
  lcd.setCursor(col, 1);
  lcd.write(1);
  lcd.write(3); 
}

void custom4(int col)
{
  lcd.setCursor(col,0);
  lcd.write(7);
  lcd.write(8);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(6);
}

void custom5(int col)
{
  lcd.setCursor(col,0);
  lcd.write(4);
  lcd.write(2);
  lcd.setCursor(col, 1);
  lcd.write(1);
  lcd.write(3);
}

void custom6(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(2);
  lcd.setCursor(col, 1);
  lcd.write(4);
  lcd.write(3);
}

void custom7(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.setCursor(col, 1);
  lcd.write(5);
  lcd.write(32);
}

void custom8(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(4);  
  lcd.write(3); 
  lcd.setCursor(col, 1); 
  lcd.write(7);  
  lcd.write(8); 
}

void custom9(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(4);  
  lcd.write(3);
  lcd.setCursor(col, 1); 
  lcd.write(1);
  lcd.write(3);
}


void printNumber(int value, int col) {
  if (value == 0) {
    custom0(col);
  } if (value == 1) {
    custom1(col);
  } if (value == 2) {
    custom2(col);
  } if (value == 3) {
    custom3(col);
  } if (value == 4) {
    custom4(col);
  } if (value == 5) {
    custom5(col);
  } if (value == 6) {
    custom6(col);
  } if (value == 7) {
    custom7(col);
  } if (value == 8) {
    custom8(col);
  } if (value == 9) {
    custom9(col);
  }      
}  
