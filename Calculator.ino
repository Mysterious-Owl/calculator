#include <Keypad.h>
#include <Wire.h> 
#include <math.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1

#define max_size  15
#define ROWS  6
#define COLS  4

char keys[ROWS][COLS] = {
  {'P','E','C','B'},
  {'%','I','^','/'},
  {'7','8','9','-'},
  {'4','5','6','*'},
  {'1','2','3','+'},
  {'0','.','A','='}
};
byte rowPins[ROWS] = {0,7,8,6,4,1}, colPins[COLS] = {2,3,5,9};
double num[max_size]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int op[max_size] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, state[max_size] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double ans=0;
int n=0,o=0,i=0,d=0;
String numa="";
bool fla=1,ans1=0,flad=0,flai=0;
char key;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

void clearall();

void setup()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
      for(;;);
  }
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.write("Calculator");
  display.display();
  display.clearDisplay();
  display.setTextSize(2);             
  display.setCursor(0, 0);
}

void loop()
{
  key = customKeypad.getKey();
  switch(key)
      {
      case '0' ... '9':
          display.write(key);
          display.display();
          if(fla)   n++,fla=0;
          if(flad)  d++;
          num[n-1] = num[n-1]*10 + (key - '0');
          ans1=0;
          break;
    
        case '+':
          if(ans1){
              display.write("Ans");
              display.display();
              num[n]=ans;
              n++;
              ans1=0;
          }
          if(flad){
            state[n-1]=d;
            num[n-1]=num[n-1]/pow(10,d);
            d=0;
            flad=0;
          }
          display.write(key);
          display.display();
          op[o] = 1;
          o++;
          fla=1;
          break;
         
        case '-':
          if(ans1){
              display.write("Ans");
              display.display();
              num[n]=ans;
              n++;
              ans1=0;
          }
          if(flad){
            state[n-1]=d;
            num[n-1]=num[n-1]/pow(10,d);
            d=0;
            flad=0;
          }
          display.write(key);
          display.display();
          op[o] = 2;
          o++;
          fla=1;
          break;
        
        case '*':
          if(ans1){
              state[n-1]=d;
              d=0;
              display.write("Ans");
              display.display();
              num[n]=ans;
              n++;
              ans1=0;
          }
          if(flad){
            state[n-1]=d;
            num[n-1]=num[n-1]/pow(10,d);
            d=0;
            flad=0;
          }
          display.print("X");
          display.display();
          op[o] = 3;
          o++;
          fla=1;
          break;
         
        case '^' :
          if(ans1){
              display.write("Ans");
              display.display();
              num[n]=ans;
              n++;
              ans1=0;
          }
          if(flad){
            state[n-1]=d;
            num[n-1]=num[n-1]/pow(10,d);
            d=0;
            flad=0;
          }
          display.write(key);
          display.display();
          op[o] = 4;
          o++;
          fla=1;
          break;
    
        case '/' :
          if(ans1){
              display.write("Ans");
              display.display();
              num[n]=ans;
              n++;
              ans1=0;
          }
          if(flad){
            state[n-1]=d;
            num[n-1]=num[n-1]/pow(10,d);
            d=0;
            flad=0;
          }
          display.write(key);
          display.display();
          op[o] = 5;
          o++;
          fla=1;
          break; 
        
        case '%' :
          if(ans1){
              state[n-1]=d;
              d=0;
              display.write("Ans");
              display.display();
              num[n]=ans;
              n++;
              ans1=0;
          }
          if(flad){
            state[n-1]=d;
            num[n-1]=num[n-1]/pow(10,d);
            d=0;
            flad=0;
          }
          display.write(key);
          display.display();
          op[o] = 6;
          o++;
          fla=1;
          break;
        
        case '=':
          display.print("  =");
          display.display();
          display.drawLine( 0,  46,  128, 46, SSD1306_WHITE );
          display.setCursor(0,48);
          if(n==0 && o==0){
            display.print("Enter something");
            display.display();
            goto againe;      
          }
          if(o!=n-1  || flai){
            display.write("Invalid syntax");
            display.display();
            goto againe;
          }
          if(flad){
            state[n-1]=d;
            num[n-1]=num[n-1]/pow(10,d);
            d=0;
            flad=0;
          }
          i=o;
          for(;;){
                if(i==0)  break;
                else{
                  int max=0, ind=-1;
                  for(int h=0;h<i;h++){
                      if(op[h]>max){
                        max=op[h];
                        ind=h;
                      }
                  }
                  switch(op[ind]){
                  
                    case 1:
                      num[ind]=num[ind]+num[ind+1];
                      break;
                    
                    case 2:
                      num[ind]=num[ind]-num[ind+1];
                      break;
                    
                    case 3:
                      num[ind]=num[ind]*num[ind+1];
                      break;
                    
                    case 4:
                      num[ind]=pow(num[ind],num[ind+1]);
                      break;
                          
                    case 5:
                      if(num[ind+1]==0){
                        display.write("Wrong Input");
                        display.display();
                        goto againe;
                      }
                      num[ind]=num[ind]/num[ind+1];
                      break;
                      
                    case 6:
                      if(num[ind+1]==0){
                        display.write("Wrong Input");
                        display.display();
                        goto againe;
                      }
                      num[ind]=int(num[ind])%int(num[ind+1]);
                      break;
                  }
                  for(int h=ind+1;h<i+1;h++){
                    op[h-1]=op[h];
                    num[h]=num[h+1];
                  }
                  if(i==6){
                    op[5]=0;
                    num[5]=0;
                  }
                  i--;
              }
          }
          numa=String(num[0],5);
          display.println(numa);
          display.display();
          ans=num[0];
          againe:
          clearall();
          break;
          
        case 'C':
          clearall();
          display.display();
          break;
          
        case 'A':
          display.write("Ans");
          display.display();
          num[n]=ans;
          state[n]=-2;
          ans1=0;
          n++;
          break;
          
        case 'P':
          clearall();
          display.setTextSize(2);
          display.println("Is Prime?");
          display.drawLine( 0,  17,  128, 17, SSD1306_WHITE );
          display.display();
          display.setCursor(0,21);
          enumber();
          display.setTextSize(2);
          clearall();
          break;
          
         case 'E':
          display.print("e");
          display.display();
          num[n]=M_E;
          state[n]=-3;
          n++;
          ans1=0;
          break;

         case 'I':
          display.print("pi");
          display.display();
          num[n]=M_PI;
          state[n]=-4;
          n++;
          ans1=0;
          break;

         case '.':
          if(flad)  flai=1;
          flad=1;
          d=0;
          display.write(key);
          display.display();
          break;

         case 'B':
             if(flad){
                state[n-1]=d;
                num[n-1]=num[n-1]/pow(10,d);
                d=0;
                flad=0;
              }
              display.clearDisplay();
              display.setCursor(0, 0);
              if(o>=n){
                int k=0;
                o--;
                op[o]=0;
                for(k=0;k<n;k++){
                  switch(state[k]){
                    case 0:
                      numa=String(num[k],0);
                      display.print(numa);
                      break;
                    case -2:
                      display.print("Ans");
                      break;
                    case -3:
                      display.print("e");
                      break;
                    case -4:
                      display.print("pi");
                      break;
                    default:
                      numa=String(num[k],state[k]);
                      display.print(numa);
                      break;
                  }
                  switch(op[k]){
                    case 1:
                      display.write("+");
                      break;
                    
                    case 2:
                      display.write("-");
                      break;
                    
                    case 3:
                      display.write("X");
                      break;
                    
                    case 4:
                      display.write("^");
                      break;
                          
                    case 5:
                      display.write("/");
                      break;
                      
                    case 6:
                      display.write("%");
                      break;
                  }
                }
                for(;k<o;k++){
                  switch(op[k]){
                    case 1:
                      display.write("+");
                      break;
                    
                    case 2:
                      display.write("-");
                      break;
                    
                    case 3:
                      display.write("X");
                      break;
                    
                    case 4:
                      display.write("^");
                      break;
                          
                    case 5:
                      display.write("/");
                      break;
                      
                    case 6:
                      display.write("%");
                      break;
                  }
                }
              }
              else{
                n--;
                for(int k=0;k<n;k++){
                  switch(state[k]){
                    case 0:
                      numa=String(num[k],0);
                      display.print(numa);
                      break;
                    case -2:
                      display.print("Ans");
                      break;
                    case -3:
                      display.print("e");
                      break;
                    case -4:
                      display.print("pi");
                      break;
                    default:
                      numa=String(num[k],state[k]);
                      display.print(numa);
                      break;
                  }
                  switch(op[k]){
                    case 1:
                      display.write("+");
                      break;
                    
                    case 2:
                      display.write("-");
                      break;
                    
                    case 3:
                      display.write("X");
                      break;
                    
                    case 4:
                      display.write("^");
                      break;
                          
                    case 5:
                      display.write("/");
                      break;
                      
                    case 6:
                      display.write("%");
                      break;
                  }
                }
                if(state[n]==0){
                  numa=String(num[n],0);
                  numa=numa.substring(0,numa.length()-1);
                  num[n]=numa.toDouble();
                  if(num[n]!=0){
                    display.print(numa);
                  }
                  else{
                    fla=1;
                    n--;
                  }
                }
                else if(state[n]>0){              
                  numa=String(num[n],state[n]);
                  state[n]--;
                  d=state[n];
                  numa=numa.substring(0,numa.length()-1);
                  num[n]=numa.toDouble()*pow(10,d);
                  display.print(numa);
                  if(state[n]!=-1) flad=1;
                }
                else{
                  num[n]=0;
                  state[n]=0;
                  n--;
                  fla=1;
                }
                n++;
              }
              display.display();
              break;
    }
}



void clearall(){
  for(int jl=0;jl<max_size;jl++){
    num[jl]=0;
    op[jl]=0;
    state[jl]=0;
  }
  i=0;
  o=0;
  ans1=1;
  n=0;
  fla=1;
  flai=0;
  flad=0;
  d=0;
  display.setCursor(0,0);
  display.clearDisplay();
}




void enumber(){
  for(;;){
     key = customKeypad.getKey();
     switch(key)
     {
      case '0' ... '9':
          display.write(key);
          display.display();
          num[0] = num[0]*10 + (key - '0');
          ans1=0;
        break;

        case 'A':
        num[0]=ans;

        case'=':
          display.setTextSize(1);
          display.setCursor(0,46);
          display.drawLine( 0,  44,  128, 44, SSD1306_WHITE );
          double l1=0;
          if(int(num[0])&1){
            for(double k=3;;k=k+2){
              l1=k*k;
              if(l1>num[0]){
                numa=String(num[0],0);
                display.print(numa);
                display.println(" is Prime");
                display.display();
                break;
              }
              else if(int(num[0])%int(k)==0){
                numa=String(num[0],0);
                display.print(numa);
                display.println(" is Composite");
                numa=String(k,0);
                display.print(numa);
                display.println(" is a factor");
                ans=k;
                display.display();
                break;
              }
            } 
          }
          else if(num[0]==2){
            numa=String(num[0],0);
            display.print(numa);
            display.println(" is Prime");
            display.display();
          }
          else{
            int k=2;
            numa=String(num[0],0);
            display.print(numa);         
            display.println(" is Composite");
            numa=String(k,0);
            display.print(numa);
            display.println(" is a factor");
            ans=k;
            display.display();
          }
          return;
     }
  }
}
