#include "LCD.h"
#include "main.h"

extern void delay_asm(uint32_t nCount);

void LCD_Master_Reset()
{
     LCD->CR = 0x00000000;
     LCD->SR = 0x00000000;
     LCD->FCR = 0x00000000;
     LCD->CLR = 0x00000000;
     LCD_RAM_clear();
}


void LCD_RAM_clear()
{
	LCD->RAM[0] = 0;
	LCD->RAM[1] = 0;
	LCD->RAM[2] = 0;
	LCD->RAM[3] = 0;
	LCD->RAM[4] = 0;
	LCD->RAM[5] = 0;
	LCD->RAM[6] = 0;
	LCD->RAM[7] = 0;
}


void LCD_bar()
{
	LCD->RAM[2] &= 0xFFFF5FFF;
	LCD->RAM[3] &= 0xFFFF5FFF;
    /* bar1 bar3 */
    LCD->RAM[2] |= ((unsigned long)((unsigned long)t_bar[0] << 0x0C));
    /*bar0 bar2 */
    LCD->RAM[3] |= ((unsigned long)((unsigned long)t_bar[1] << 0x0C));
}


void LCD_GLASS_WriteChar(unsigned char *ch, unsigned char point, unsigned char column, unsigned char position)
{
    unsigned char digit[0x04];     /* Digit frame buffer */

    /* To convert displayed character in segment in array digit */
    LCD_Conv_Char_Seg(ch, point, column, digit);
    /* TO wait LCD Ready */
    while(LCD->SR & LCD_SR_UDR);

    switch (position)
    {
        /* Position 1 on LCD (Digit1)*/
        case 1:
        {
        	LCD->RAM[0] &= 0xCFFFFFFC;
        	LCD->RAM[2] &= 0xCFFFFFFC;
        	LCD->RAM[4] &= 0xCFFFFFFC;
        	LCD->RAM[6] &= 0xCFFFFFFC;

        	LCD->RAM[0] |= (((((unsigned long)digit[0x00]) & 0x0C) << 0x1A) | (((unsigned long)digit[0x00]) & 0x03)); // 1G 1B 1M 1E
        	LCD->RAM[2] |= (((((unsigned long)digit[0x01]) & 0x0C) << 0x1A) | (((unsigned long)digit[0x01]) & 0x03)); // 1F 1A 1C 1D
        	LCD->RAM[4] |= (((((unsigned long)digit[0x02]) & 0x0C) << 0x1A) | (((unsigned long)digit[0x02]) & 0x03)); // 1Q 1K 1Col 1P
        	LCD->RAM[6] |= (((((unsigned long)digit[0x03]) & 0x0C) << 0x1A) | (((unsigned long)digit[0x03]) & 0x03)); // 1H 1J 1DP 1N

            break;
         }

        /* Position 2 on LCD (Digit2)*/
        case 2:
        {
        	LCD->RAM[0] &= 0xF3FFFF03;
        	LCD->RAM[2] &= 0xF3FFFF03;
        	LCD->RAM[4] &= 0xF3FFFF03;
        	LCD->RAM[6] &= 0xF3FFFF03;

        	LCD->RAM[0] |= (((((unsigned long)digit[0x00]) & 0x0C) << 0x18) | ((((unsigned long)digit[0x00]) & 0x02) << 0x06) | ((((unsigned long)digit[0x00]) & 0x01) << 0x02)); // 2G 2B 2M 2E
        	LCD->RAM[2] |= (((((unsigned long)digit[0x01]) & 0x0C) << 0x18) | ((((unsigned long)digit[0x01]) & 0x02) << 0x06) | ((((unsigned long)digit[0x01]) & 0x01) << 0x02)); // 2F 2A 2C 2D
        	LCD->RAM[4] |= (((((unsigned long)digit[0x02]) & 0x0C) << 0x18) | ((((unsigned long)digit[0x02]) & 0x02) << 0x06) | ((((unsigned long)digit[0x02]) & 0x01) << 0x02)); // 2Q 2K 2Col 2P
        	LCD->RAM[6] |= (((((unsigned long)digit[0x03]) & 0x0C) << 0x18) | ((((unsigned long)digit[0x03]) & 0x02) << 0x06) | ((((unsigned long)digit[0x03]) & 0x01) << 0x02)); // 2H 2J 2DP 2N

            break;
         }

        /* Position 3 on LCD (Digit3)*/
        case 3:
        {
            LCD->RAM[0] &= 0xFCFFFCFF;
            LCD->RAM[2] &= 0xFCFFFCFF;
            LCD->RAM[4] &= 0xFCFFFCFF;
            LCD->RAM[6] &= 0xFCFFFCFF;

            LCD->RAM[0] |= (((((unsigned long)digit[0x00]) & 0x0C) << 0x16) | ((((unsigned long)digit[0x00]) & 0x03) << 0x08)); // 3G 3B 3M 3E
            LCD->RAM[2] |= (((((unsigned long)digit[0x01]) & 0x0C) << 0x16) | ((((unsigned long)digit[0x01]) & 0x03) << 0x08)); // 3F 3A 3C 3D
            LCD->RAM[4] |= (((((unsigned long)digit[0x02]) & 0x0C) << 0x16) | ((((unsigned long)digit[0x02]) & 0x03) << 0x08)); // 3Q 3K 3Col 3P
            LCD->RAM[6] |= (((((unsigned long)digit[0x03]) & 0x0C) << 0x16) | ((((unsigned long)digit[0x03]) & 0x03) << 0x08)); // 3H 3J 3DP 3N

            break;
         }

        /* Position 4 on LCD (Digit4)*/
        case 4:
        {
            LCD->RAM[0] &= 0xFFCFF3FF;
            LCD->RAM[2] &= 0xFFCFF3FF;
            LCD->RAM[4] &= 0xFFCFF3FF;
            LCD->RAM[6] &= 0xFFCFF3FF;

            LCD->RAM[0] |= (((((unsigned long)digit[0x00]) & 0x0C) << 0x12) | ((((unsigned long)digit[0x00]) & 0x03) << 0x0A)); // 4G 4B 4M 4E
            LCD->RAM[2] |= (((((unsigned long)digit[0x01]) & 0x0C) << 0x12) | ((((unsigned long)digit[0x01]) & 0x03) << 0x0A)); // 4F 4A 4C 4D
            LCD->RAM[4] |= (((((unsigned long)digit[0x02]) & 0x0C) << 0x12) | ((((unsigned long)digit[0x02]) & 0x03) << 0x0A)); // 4Q 4K 4Col 4P
            LCD->RAM[6] |= (((((unsigned long)digit[0x03]) & 0x0C) << 0x12) | ((((unsigned long)digit[0x03]) & 0x03) << 0x0A)); // 4H 4J 4DP 4N

            break;
         }

        /* Position 5 on LCD (Digit5)*/
        case 5:
        {
            LCD->RAM[0] &= 0xFFF3CFFF;
            LCD->RAM[2] &= 0xFFF3CFFF;
            LCD->RAM[4] &= 0xFFF3CFFF;
            LCD->RAM[6] &= 0xFFF3CFFF;

            LCD->RAM[0] |= (((((unsigned long)digit[0x00]) & 0x0C) << 0x10) | ((((unsigned long)digit[0x00]) & 0x03) << 0x0C)); // 5G 5B 5M 5E
            LCD->RAM[2] |= (((((unsigned long)digit[0x01]) & 0x0C) << 0x10) | ((((unsigned long)digit[0x01]) & 0x03) << 0x0C)); // 5F 5A 5C 5D
            LCD->RAM[4] |= (((((unsigned long)digit[0x02]) & 0x0C) << 0x10) | ((((unsigned long)digit[0x02]) & 0x01) << 0x0C)); // 5Q 5K   5P
            LCD->RAM[6] |= (((((unsigned long)digit[0x03]) & 0x0C) << 0x10) | ((((unsigned long)digit[0x03]) & 0x01) << 0x0C)); // 5H 5J   5N

            break;
         }

        /* Position 6 on LCD (Digit6)*/
        case 6:
        {
            LCD->RAM[0] &= 0xFFFC3FFF;
            LCD->RAM[2] &= 0xFFFC3FFF;
            LCD->RAM[4] &= 0xFFFC3FFF;
            LCD->RAM[6] &= 0xFFFC3FFF;

            LCD->RAM[0] |= (((((unsigned long)digit[0x00]) & 0x04) << 0x0F) | ((((unsigned long)digit[0x00]) & 0x08) << 0x0D) | ((((unsigned long)digit[0x00]) & 0x03) << 0x0E)) ; // 6B 6G 6M 6E
            LCD->RAM[2] |= (((((unsigned long)digit[0x01]) & 0x04) << 0x0F) | ((((unsigned long)digit[0x01]) & 0x08) << 0x0D) | ((((unsigned long)digit[0x01]) & 0x03) << 0x0E)) ; // 6A 6F 6C 6D
            LCD->RAM[4] |= (((((unsigned long)digit[0x02]) & 0x04) << 0x0F) | ((((unsigned long)digit[0x02]) & 0x08) << 0x0D) | ((((unsigned long)digit[0x02]) & 0x01) << 0x0E)) ; // 6K 6Q    6P
            LCD->RAM[6] |= (((((unsigned long)digit[0x03]) & 0x04) << 0x0F) | ((((unsigned long)digit[0x03]) & 0x08) << 0x0D) | ((((unsigned long)digit[0x03]) & 0x01) << 0x0E)) ; // 6J 6H   6N

            break;
         }

         default:
         {
            break;
         }
    }

    /* Refresh LCD  bar */
    LCD_bar();
//    update_display_request();
    LCD->SR |= LCD_SR_UDR;
}


void LCD_GLASS_DisplayString(unsigned char *ptr)
{
    unsigned char i = 0x01;

    /* Send the string character by character on lCD */
    while((*ptr != 0) & (i < 0x08))
    {
        /* Display one character on LCD */
        LCD_GLASS_WriteChar(ptr, false, false, i);

        /* Point on the next character */
        ptr++;
        /* Increment the character counter */
        i++;
    }
}


void LCD_GLASS_DisplayStrDeci(unsigned int *ptr)
{
    unsigned char i = 0x01;
    unsigned char char_tmp = 0x00;

    //  LCD_GLASS_Clear();
    /* Send the string character by character on lCD */
    while((*ptr != 0) & (i < 0x08))
    {
        char_tmp = ((*ptr) & 0x00FF);

        switch((*ptr) & 0xF000)
        {
            case DOT:
            {
                /* Display one character on LCD with decimal point */
                LCD_GLASS_WriteChar(&char_tmp, POINT_ON, COLUMN_OFF, i);
                break;
            }
            case DOUBLE_DOT:
            {
                /* Display one character on LCD with decimal point */
                LCD_GLASS_WriteChar(&char_tmp, POINT_OFF, COLUMN_ON, i);
                break;
            }
            default:
            {
                LCD_GLASS_WriteChar(&char_tmp, POINT_OFF, COLUMN_OFF, i);
                break;
            }
        }/* Point on the next character */
        ptr++;
        /* Increment the character counter */
        i++;
    }
}


void LCD_GLASS_Clear()
{
    /* TO wait LCD Ready */
	while(LCD->SR & LCD_SR_UDR);
	LCD_RAM_clear();
    /* Update the LCD display */
//    update_display_request();
	LCD->SR |= LCD_SR_UDR;
}


void LCD_GLASS_ScrollSentence(unsigned char *ptr, unsigned int nScroll, unsigned int ScrollSpeed) {
    unsigned char Repetition = 0x00;
    unsigned char Char_Nb = 0x00;
    unsigned char *ptr1;
    unsigned char str[7] = "";
    unsigned char Str_size = 0x00;

    if(ptr == 0)
    {
        return;
    }

    /* To calculate end of string */
    for(ptr1 = ptr, Str_size = 0x00 ; *ptr1 != 0x00; Str_size++, ptr1++)
    {
    };

    ptr1 = ptr;
    LCD_GLASS_DisplayString(ptr);
//    HAL_Delay(ScrollSpeed);
    delay_asm(ScrollSpeed);

    /* To shift the string for scrolling display*/
    for(Repetition = 0x00; Repetition < nScroll; Repetition++)
    {
        for(Char_Nb = 0x00; Char_Nb < Str_size; Char_Nb++)
        {
              *(str) = *(ptr1 + ((Char_Nb + 0x01) % Str_size));
              *(str + 0x01) = *(ptr1 + ((Char_Nb + 0x02) % Str_size));
              *(str + 0x02) = *(ptr1 + ((Char_Nb + 0x03) % Str_size));
              *(str + 0x03) = *(ptr1 + ((Char_Nb + 0x04) % Str_size));
              *(str + 0x04) = *(ptr1 + ((Char_Nb + 0x05) % Str_size));
              *(str + 0x05) = *(ptr1 + ((Char_Nb + 0x06) % Str_size));
              LCD_GLASS_Clear();
              LCD_GLASS_DisplayString(str);

//              HAL_Delay(ScrollSpeed);
              delay_asm(ScrollSpeed);
        }
    }
}


static void LCD_Conv_Char_Seg(unsigned char *c, unsigned char point, unsigned char column, unsigned char *digit)
{
    unsigned char i = 0x00;
    unsigned char j = 0x00;

    unsigned int ch = 0x0000;

    switch(*c)
    {
        case ' ':
        {
            ch = 0x00;
            break;
        }
        case '*':
        {
            ch = star;
            break;
        }
        case '&':
        {
            ch = C_UMAP;
            break;
        }
        case 'm':
        {
            ch = C_mMap;
            break;
        }
        case 'n':
        {
            ch = C_nMap;
            break;
        }
        case '-':
        {
            ch = C_minus;
            break;
        }
        case '/':
        {
            ch = C_slatch;
            break;
        }
        case '?':
        {
            ch = C_percent_1;
            break;
        }
        case '%':
        {
            ch = C_percent_2;
            break;
        }
        case '[':
        {
            ch = bracket_open;
            break;
        }
        case ']':
        {
            ch = bracket_close;
            break;
        }
        case 0xFF:
        {
            ch = C_full;
            break;
        }
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            ch = NumberMap[(*c - 0x30)];
            break;
        }
        default:
        {
            /* The character c is one letter in upper case*/
            if((*c < 0x5B) && (*c > 0x40))
            {
                ch = CapLetterMap[(*c - 'A')];
            }
            /* The character c is one letter in lower case*/
            if((*c <0x7B) && (*c > 0x60))
            {
                ch = SmallLetterMap[(*c - 'a')];
            }
            break;
        }
    }

    /* Set the digital point can be displayed if the point is on */
    if(point != 0)
    {
        ch |= 0x0002;
    }

    /* Set the "COL" segment in the character that can be displayed if the column is on */
    if(column != 0)
    {
        ch |= 0x0020;
    }

    for(i = 0x0C, j = 0x00 ; j < 0x04; i -= 0x04, j++)
    {
        digit[j] = ((ch >> i) & 0x0F); //To isolate the less signifiant bit
    }
}
