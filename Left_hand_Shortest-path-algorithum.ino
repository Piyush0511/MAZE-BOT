char directions[30];
char reshortn[30];
char shortn[30];
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

int lm1=24,lm2=25,rm1=0,rm2=1;
int l,c1,c2,c3,r;
int i,j,k;
int tdelay=700;
int fdelay=500;
int udelay=1800;

void Forward()
{
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}


void Stop()
{
  digitalWrite(lm1,0);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,0);
}


void Reverse()
{
  digitalWrite(lm1,0);
  digitalWrite(lm2,1);
  digitalWrite(rm1,0);
  digitalWrite(rm2,1);
}


void Right()
{
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,1);
}


void Left()
{
  digitalWrite(lm1,0);
  digitalWrite(lm2,1);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}

void smallright()
{
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,0);
}


void smallleft()
{
  digitalWrite(lm1,0);
  digitalWrite(lm2,0);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}

int eosens()
{
  readsens();
  if(((c1+c2+c3)==1)||((c1+c2+c3)==2))
    return 1;
  else 
    return 0;
}

void readsens()
{
  l=digitalRead(26);
  c1=digitalRead(27);
  c2=digitalRead(28);
  c3=digitalRead(29);
  r=digitalRead(30);

  lcd.print(l);
  lcd.print("-");
  lcd.print(c1);
  lcd.print("-");
  lcd.print(c2);
  lcd.print("-");
  lcd.print(c3);
  lcd.print("-");
  lcd.print(r);
  lcd.print("-");
}

void inch()
{
  lcd.print("Inch Function");
  //delay(100);
  Stop();
  delay(100);
  Forward();
  delay(500);
  Stop();
  delay(50);
  readsens();
  //delay(100);
  lcd.clear();
}

void align()
{
  Stop();
  delay(500);
  Forward();
  delay(60);
  lcd.clear();
  readsens();
}

void printing(char prtdirection[])
{
  lcd.clear();
  for(i=0;prtdirection[i]!='E';i++)
  {
    lcd.print(prtdirection[i]);
  }
  delay(2000);
}

void setup()
{
  lcd.begin(16,2);
  lcd.print("#ONE LAST RIDE");
  delay(500);
  lcd.clear();

  pinMode(lm1,OUTPUT);
  pinMode(lm2,OUTPUT);
  pinMode(rm1,OUTPUT);
  pinMode(rm2,OUTPUT);
  pinMode(26,INPUT);
  pinMode(27,INPUT);
  pinMode(28,INPUT);
  pinMode(29,INPUT);
  pinMode(30,INPUT);
}

void loop()
{
  lcd.clear();
  readsens();
  lcd.clear();

  //Line Follow
  //fwd

  if((l==1)&&(c1==1)&&(c2==0)&&(c3==1)&&(r==1))
  {
    lcd.print("Forward");
    Forward();
    delay(10);

  }

  //left
  else if(((l==1)&&(c1==0)&&(c2==1)&&(c3==1)&&(r==1))||((l==1)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1)))
  {
    lcd.print("Small Left");
    smallleft();

  }
  //Right 
  else if(((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==1))||((l==1)&&(c1==1)&&(c2==1)&&(c3==0)&&(r==1)))
  {
    lcd.print("Small Right");
    smallright();

  }

  //Dead end

  else if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
  {
    lcd.print("U turn");
    Left();
    delay(udelay);
    directions[i]='U';
    i++;
  }

  else if(((l==0)&&(c1==0))||((c3==0)&&(r==0)))
  {
    align();


    //Right only or str right

    if(((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==0))||((l==1)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0)))
    {
      lcd.print("Rt/Str n Rt?");
      inch();


      if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
      {
        lcd.print("right");
        Right();
        delay(tdelay);
      }

      else if((l==1)&&(r==1)&&(eosens()))
      {
        lcd.print("Straight");
        directions[i]='S';
        i++;
        Forward();
        delay(fdelay);
      }
    }

    //left or straight and left
    if(((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==1))||((l==0)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1)))
    {
      lcd.print("Lt/Str n Lt?");
      inch();


      if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r=1))
      {
        lcd.print("Left");
        Left();
        delay(tdelay);
      }

      else if((l==1)&&(r==1)&&(eosens()))
      {
        lcd.print("Left");
        directions[i]='L';
        i++;
        Left();
        delay(tdelay);
      }
    }



    //4 way/T-tint/End of maze

    if((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))
    {
      lcd.print("T/END/4");
      inch();
      if((l==1)&&(r==1)&&(eosens()))
      {
        lcd.print("4 Way");
        directions[i]='L';
        i++;
        Left();
        delay(tdelay);
      }

      else if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
      {
        lcd.print("T-int");
        directions[i]='L';
        i++;
        Left();
        delay(tdelay);
      }

      else if((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))
      {
        lcd.print("End of maze");
        directions[i]='E';
        printing(directions);     
        Stop();
        delay(5000);
        lcd.clear();
        replacement(directions);
      }
    }

  }
}

//SHORTEST PATH ALHORITHM
void replacement(char shortn[])

{
  lcd.print("Entered Replacement");
  delay(1000);
  lcd.clear();

  for(i=0;shortn[i+1]!='E';i++)
  {
    if(shortn[i]=='U')
    {
      if((shortn[i-1]=='S')&&(shortn[i+1]=='L'))
      {
        shortn[i-1]='x';
        shortn[i]='x';
        shortn[i+1]='R';
      }

      else if((shortn[i-1]=='L')&&(shortn[i+1]=='L'))
      {
        shortn[i-1]='x';
        shortn[i]='x';
        shortn[i+1]='S';
      }

      else if((shortn[i-1]=='L')&&(shortn[i+1]=='S'))
      {
        shortn[i-1]='x';
        shortn[i]='x';
        shortn[i+1]='R';
      }

      else if((shortn[i-1]=='L')&&(shortn[i+1]=='R'))
      {
        shortn[i-1]='x';
        shortn[i]='x';
        shortn[i+1]='U';
      }

      else if((shortn[i-1]=='R')&&(shortn[i+1]=='L'))
      {
        shortn[i-1]='x';
        shortn[i]='x';
        shortn[i+1]='U';
      }

      else if((shortn[i-1]=='S')&&(shortn[i+1]=='S'))
      {
        shortn[i-1]='x';
        shortn[i]='x';
        shortn[i+1]='U';
      }
    }
  }

  lcd.clear();
  lcd.print("Finished New Path");
  delay(1000);
  lcd.print("New");
  j=0;
  for(i=0;shortn[i]!='E';i++)
  {
    if(shortn[i]!='x')
    {
      reshortn[j]=shortn[i];
      j++;
    }
  }

  reshortn[j]='E';
  lcd.print("SPA=");
  printing(reshortn);
  delay(1000);

  for(i=0;reshortn[i]!='E';i++)
  {
    if(reshortn[i]=='U')
    {
      replacement(reshortn);
    }
  }

  lcd.clear();
  lcd.print("FINAL=");
  printing(reshortn);
  final();
}

void decisions()
{
  lcd.print("Entered Decisions");
  lcd.clear();

  if(reshortn[k]=='S')
  {
    Forward();
    delay(fdelay);
  }

  else if(reshortn[k]=='L')
  {
    Left();
    delay(tdelay);
  }

  else if(reshortn[k]=='R')
  {
    Right();
    delay(tdelay);
  }
  k++;
}

//FINAL

void final()
{
  lcd.clear();
  lcd.print("Entered Final");

  while(1)
  {
    readsens();

    if((l==1)&&(c1==1)&&(c2==0)&&(c3==1)&&(r==1))
    {

      Forward();
      delay(10);

    }

    //left
    else if(((l==1)&&(c1==0)&&(c2==1)&&(c3==1)&&(r==1))||((l==1)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1)))
    {

      smallleft();

    }
    //Right 
    else if(((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==1))||((l==1)&&(c1==1)&&(c2==1)&&(c3==0)&&(r==1)))
    {

      smallright();

    }

    else if(((l==0)&&(c1==0))||((c3==0)&&(r==0)))
    {
      align();


      //Right only or str right

      if(((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==0))||((l==1)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0)))
      {
        
        inch();


        if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
        {
          
          Right();
          delay(tdelay);
        }

        else if((l==1)&&(r==1)&&(eosens()))
        {
          decisions();

        }
      }

      //left or straight and left
      else if(((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==1))||((l==0)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1)))
      {
        
        inch();


        if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r=1))
        {
          lcd.print("Left");
          Left();
          delay(tdelay);
        }

        else if((l==1)&&(r==1)&&(eosens()))
        {
          lcd.print("St n Lt");
          decisions();
        }
      }



      //4 way/T-tint/End of maze

      else if((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))
      {
        
        inch();
        if((l==1)&&(r==1)&&(eosens()))
        {
          decisions();
        }

        else if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))
        {
          decisions();
        }

        else if((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))
        {
          lcd.print("End of maze");
          while(1)
          {
            Stop();
          }
        }
      }

    }
  }
}












