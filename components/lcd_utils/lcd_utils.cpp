#include "lcd_utils.hpp"


#define TAG "lcd_utils"

const unsigned int white = 0xffffffu;
const unsigned int black = 0x000000u;

void drawPage(LGFX_LiLyGo_TDongleS3 &lcd, int page, int numPages, const char *title, const char *text)
{
  lcd.clear(black);

  // Calculate the x and y coordinates of the title text (centering it on the screen)
  int title_size = 2;
  int title_x = (DISPLAY_WIDTH - (strlen(title) * 6*title_size)) / 2;
  int title_y = (DISPLAY_HEIGHT / 2) - 10*title_size;
 
  lcd.setColor(white);
  lcd.setCursor(title_x, title_y);
  lcd.setTextColor(white, black);
  lcd.setTextSize(title_size);
  lcd.println(title);

  // Calculate the x and y coordinates of the text (centering it on the screen and below the title)
  int text_size = 1;
  int text_x = (DISPLAY_WIDTH - (strlen(text) * 6*text_size)) / 2;
  int text_y = (DISPLAY_HEIGHT / 2) + 10*text_size;

  lcd.setCursor(text_x, text_y);
  lcd.setTextColor(white, black);
  lcd.setTextSize(text_size);
  lcd.println(text);

  // Write the page number at the end of the screen
  int page_x = (DISPLAY_WIDTH - (strlen("x/x") * 6)) / 2;
  int page_y = DISPLAY_HEIGHT - 10;
  lcd.setCursor(page_x, page_y);
  lcd.setTextColor(white, black);
  lcd.printf("%d/%d", page, numPages);
  return;
}