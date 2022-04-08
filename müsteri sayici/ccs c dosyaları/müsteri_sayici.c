#include <m�steri_sayici.h>
int16 toplam_kisi=0;//toplam icin
int16 icerdeki_kisi=0;//i�erde ka� ki�i 
int16 fark=0;//fark de�eri

#INT_RTCC// TMR0 kesmesi 
void  RTCC_isr(void) //TMR0 kesme alt program�
{

set_timer0(255);// bu degerden baslatarak hemen s�f�rlanmas� sa�lan�yor
toplam_kisi++;//toplam_kisi degerini 1 artir

}

#INT_EXT//RB0 di� kesme programi
void  EXT_isr(void) 
{
if(fark>0)// magaza hic kimse giris yapmamasi durumunda icerdeki kisi degeri nagatif deger almasin
icerdeki_kisi++;//i�erdeki_kisi degeri 1 artir

}
#define LCD_ENABLE_PIN PIN_B1//lcd ekran baglanti pinleri
#define LCD_RS_PIN PIN_B2
#define LCD_RW_PIN PIN_B3
#define LCD_DATA4 PIN_B4
#define LCD_DATA5 PIN_B5
#define LCD_DATA6 PIN_B6
#define LCD_DATA7 PIN_B7

#include <lcd.c>//lcd ekran kullanim kutuphanesi

void main()//bir sefer �ali�acak kodlar 
{
   
   setup_timer_0(RTCC_EXT_L_TO_H|RTCC_DIV_1|RTCC_8_bit);//d�sen kenardan y�kselen kenara dogri kesme,0-256 arasi 
   ext_int_edge(L_to_H);//RB0 dis kesmesi d�sen kenardan y�kselen kenara dogri
   enable_interrupts(INT_RTCC);//RTCC kesme izin ver
   enable_interrupts(INT_EXT);//EXT  dis kesme izin ver
   enable_interrupts(GLOBAL);// t�m kesmeler acik
   set_timer0(255);//timer 0 ba�langic degeri

   lcd_init();//lcd ekran kullan�ma a�
   
   lcd_gotoxy(1,1);//LCD ekran konum belirle
   printf(lcd_putc,"\f CAN BAKKAL");//ekrani temizle metini ekrana yazdir
   delay_ms(1000);//bir saniye bekle



   while(TRUE)//sonsuz dongu kisimi
   {
      

   fark=toplam_kisi-icerdeki_kisi;//iceride kac kisi oldugu fark degiskenine kayit ediliyor
  
   lcd_gotoxy(1,2);//LCD ekran konumlandirma
   printf(lcd_putc,"top=%ld",toplam_kisi);// toplam kisi ekrana yaz
   delay_ms(10);
   lcd_gotoxy(8,2);
   printf(lcd_putc,"ic= %ld",fark);//icerdeki kisi sayisini ekrana yaz
   delay_ms(10);
   
   
   
   
   }

}
