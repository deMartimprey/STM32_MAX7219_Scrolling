#include "matrix.h"

void init_matrix()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = PIN_MATRIX_CLK;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PORT_MATRIX_CLK, &GPIO_InitStruct);
  HAL_GPIO_WritePin(PORT_MATRIX_CLK, PIN_MATRIX_CLK, GPIO_PIN_SET);

  GPIO_InitStruct.Pin = PIN_MATRIX_CS;
  HAL_GPIO_Init(PORT_MATRIX_CS, &GPIO_InitStruct);
  HAL_GPIO_WritePin(PORT_MATRIX_CS, PIN_MATRIX_CS, GPIO_PIN_SET);

  GPIO_InitStruct.Pin = PIN_MATRIX_DIN;
  HAL_GPIO_Init(PORT_MATRIX_DIN, &GPIO_InitStruct);
  HAL_GPIO_WritePin(PORT_MATRIX_DIN, PIN_MATRIX_CS, GPIO_PIN_SET);
}

#define LENGTH_1	18

void demo_matrix()
{
  init_matrix();
  max_init();
  uint8_t* matrix_tab[LENGTH_1 + 1] = {0, };
  uint8_t letter0[8] = {0, };
  uint8_t letter1[8] = {0, };
  uint8_t letter2[8] = {0, };
  uint8_t letter3[8] = {0, };
  uint8_t letter4[8] = {0, };
  uint8_t letter5[8] = {0, };
  uint8_t letter6[8] = {0, };
  uint8_t letter7[8] = {0, };
  uint8_t letter8[8] = {0, };
  uint8_t letter9[8] = {0, };
  uint8_t letter10[8] = {0, };
  uint8_t letter11[8] = {0, };
  uint8_t letter12[8] = {0, };
  uint8_t letter13[8] = {0, };
  uint8_t letter14[8] = {0, };
  uint8_t letter15[8] = {0, };
  uint8_t letter16[8] = {0, };
  uint8_t letter17[8] = {0, };

  matrix_tab[0] = letter0;
  matrix_tab[1] = letter1;
  matrix_tab[2] = letter2;
  matrix_tab[3] = letter3;
  matrix_tab[4] = letter4;
  matrix_tab[5] = letter5;
  matrix_tab[6] = letter6;
  matrix_tab[7] = letter7;
  matrix_tab[8] = letter8;
  matrix_tab[9] = letter9;
  matrix_tab[10] = letter10;
  matrix_tab[11] = letter11;
  matrix_tab[12] = letter12;
  matrix_tab[13] = letter13;
  matrix_tab[14] = letter14;
  matrix_tab[15] = letter15;
  matrix_tab[16] = letter16;
  matrix_tab[17] = letter17;

  fill_matrix_tab((uint8_t**)matrix_tab, (uint8_t*)STRING_DEMO, LENGTH_1);
  turn_matrix_tab((uint8_t**)matrix_tab, LENGTH_1);
  inverse_matrix_tab((uint8_t**)matrix_tab, LENGTH_1);
  print_matrix_tab((uint8_t**)matrix_tab, 4);
  HAL_Delay(200);
  for (int i = 0; i < 8 * (LENGTH_1 - 4); i++)
    {
      decal_1_right((uint8_t**)matrix_tab, LENGTH_1);
      print_matrix_tab((uint8_t**)matrix_tab, 4);
      HAL_Delay(18);
    }
  HAL_Delay(600);
  for (int i = 0; i < 8 * (LENGTH_1 - 4); i++)
    {
      decal_1_left((uint8_t**)matrix_tab, LENGTH_1);
      print_matrix_tab((uint8_t**)matrix_tab, 4);
      HAL_Delay(4);
    }
}

void max_init(void)
{
  /* blank_all_matrice(); */
  write_max(0x09, 0x00);       //  no decoding
  write_max(0x0a, 0x03);       //  brightness intensity
  write_max(0x0b, 0x07);       //  scan limit = 8 LEDs
  write_max(0x0c, 0x01);       //  power down =0，normal mode = 1
  write_max(0x0f, 0x00);       //  no test display
}

void write_byte(uint8_t byte)
{
  for(int i=0;i<8;i++)
    {
      HAL_GPIO_WritePin(PORT_MATRIX_CLK, PIN_MATRIX_CLK, 0);  // Pull the CLK LOW
      HAL_GPIO_WritePin(PORT_MATRIX_DIN, PIN_MATRIX_DIN, byte&0x80);// Write one BIT data MSB first
      byte = byte<<1;  // shift the data to the left
      HAL_GPIO_WritePin(PORT_MATRIX_CLK, PIN_MATRIX_CLK, 1);  // Pull the CLK HIGH
    }
}

void write_max(uint8_t address, uint8_t data)
{
  HAL_GPIO_WritePin(PORT_MATRIX_CS, PIN_MATRIX_CS, 0);   // Pull the CS pin LOW
  for (int i = 0; i < NB_MATRIX; i++)
    {
      write_byte(address);   //  write address
      write_byte(data);  //  write data
    }
  HAL_GPIO_WritePin(PORT_MATRIX_CS, PIN_MATRIX_CS, 1);  // pull the CS HIGH
}

void write_x_max(uint8_t dot, uint8_t address, uint8_t data)
{
  HAL_GPIO_WritePin(PORT_MATRIX_CS, PIN_MATRIX_CS, 0);   // Pull the CS pin LOW
  if (dot == 0)
    {
      write_byte(0x00);   //  write address
      write_byte(0x00);  //  write data
      write_byte(0x00);   //  write address
      write_byte(0x00);  //  write data
      write_byte(0x00);   //  write address
      write_byte(0x00);  //  write data
    }
  if (dot == 1)
    {
      write_byte(0x00);   //  write address
      write_byte(0x00);  //  write data
      write_byte(0x00);   //  write address
      write_byte(0x00);  //  write data
    }
  if (dot == 2)
    {
      write_byte(0x00);   //  write address
      write_byte(0x00);  //  write data
    }
  write_byte(address);   //  write address
  write_byte(data);  //  write data
  while (dot > 0)
    {
      write_byte(0x00);   //  write address
      write_byte(0x00);  //  write data
      dot--;
    }
  HAL_GPIO_WritePin(PORT_MATRIX_CS, PIN_MATRIX_CS, 1);  // pull the CS HIGH
}

void print_matrix_tab_first(uint8_t** matrix_tab, uint8_t size)
{
  uint8_t* letter_ptr;
  /* for (int8_t i = 0; i < size && i < size; i++) */
  /*   { */
     letter_ptr = matrix_tab[0];

     write_x_max(0, 0x01, letter_ptr[0]);
     write_x_max(0, 0x02, letter_ptr[1]);
     write_x_max(0, 0x03, letter_ptr[2]);
     write_x_max(0, 0x04, letter_ptr[3]);
     write_x_max(0, 0x05, letter_ptr[4]);
     write_x_max(0, 0x06, letter_ptr[5]);
     write_x_max(0, 0x07, letter_ptr[6]);
     write_x_max(0, 0x08, letter_ptr[7]);
    /* } */
}

void print_matrix_tab(uint8_t** matrix_tab, uint8_t size)
{
  uint8_t* letter_ptr;

  led += 1;
  if (led > 2)
    {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
      led = 0;
    }
  else
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
  for (int8_t i = 0; i < size && i < 4; i++)
    {
     letter_ptr = matrix_tab[i];

     write_x_max(i, 0x01, letter_ptr[0]);
     write_x_max(i, 0x02, letter_ptr[1]);
     write_x_max(i, 0x03, letter_ptr[2]);
     write_x_max(i, 0x04, letter_ptr[3]);
     write_x_max(i, 0x05, letter_ptr[4]);
     write_x_max(i, 0x06, letter_ptr[5]);
     write_x_max(i, 0x07, letter_ptr[6]);
     write_x_max(i, 0x08, letter_ptr[7]);
    }
}


void print_one_letter_lvl(uint8_t matrice, uint8_t letter)
{
  uint8_t letter_tab[8] = {0, };
  uint8_t* letter_ptr;
  for (uint8_t i = 0; i < 8; i++)
    {
      letter_tab[i] = MAX7219_Dot_Matrix_font[letter - 0x20][i];
    }
  uint8_t right_letter[8];
  uint8_t right_letter2[8];
  uint8_t right_letter3[8];
  letter_ptr = letter_tab;
  letter_ptr = turn_letter((uint8_t*)&right_letter, letter_ptr);
  letter_ptr = inverse_letter((uint8_t*)&right_letter3, letter_ptr);
  letter_ptr = turn_letter((uint8_t*)&right_letter2, letter_ptr);
  letter_ptr = inverse_letter((uint8_t*)&right_letter3, letter_ptr);
  decal_letter_tab_2((uint8_t**)&letter_ptr, 1);

  write_x_max(matrice, 0x01, letter_ptr[0]);
  write_x_max(matrice, 0x02, letter_ptr[1]);
  write_x_max(matrice, 0x03, letter_ptr[2]);
  write_x_max(matrice, 0x04, letter_ptr[3]);
  write_x_max(matrice, 0x05, letter_ptr[4]);
  write_x_max(matrice, 0x06, letter_ptr[5]);
  write_x_max(matrice, 0x07, letter_ptr[6]);
  write_x_max(matrice, 0x08, letter_ptr[7]);
}

void print_one_letter(uint8_t matrice, uint8_t letter)
{
  uint8_t letter_tab[8] = {0, };
  uint8_t* letter_ptr;
  for (uint8_t i = 0; i < 8; i++)
    {
      letter_tab[i] = MAX7219_Dot_Matrix_font[letter - 0x20][i];
    }
  letter_ptr = letter_tab;

  write_x_max(matrice, 0x01, letter_ptr[0]);
  write_x_max(matrice, 0x02, letter_ptr[1]);
  write_x_max(matrice, 0x03, letter_ptr[2]);
  write_x_max(matrice, 0x04, letter_ptr[3]);
  write_x_max(matrice, 0x05, letter_ptr[4]);
  write_x_max(matrice, 0x06, letter_ptr[5]);
  write_x_max(matrice, 0x07, letter_ptr[6]);
  write_x_max(matrice, 0x08, letter_ptr[7]);
}

void print_four_letter(uint8_t* letter)
{
  print_one_letter(0, letter[0]);
  print_one_letter(1, letter[1]);
  print_one_letter(2, letter[2]);
  print_one_letter(3, letter[3]);
}

void blank_matrice(uint8_t matrice)
{
  write_x_max(matrice, 0x01, 0b00000000);
  write_x_max(matrice, 0x02, 0b00000000);
  write_x_max(matrice, 0x03, 0b00000000);
  write_x_max(matrice, 0x04, 0b00000000);
  write_x_max(matrice, 0x05, 0b00000000);
  write_x_max(matrice, 0x06, 0b00000000);
  write_x_max(matrice, 0x07, 0b00000000);
  write_x_max(matrice, 0x08, 0b00000000); 
}

void blank_all_matrice()
{
  blank_matrice(0);
  blank_matrice(1);
  blank_matrice(2);
  blank_matrice(3);
}

uint8_t* inverse_letter(uint8_t* res, uint8_t* letter)
{
  uint8_t tmp = 0;
  uint8_t count;

  for(uint8_t i = 0; i < 8; i++) {
    count = 7;
    for(uint8_t j = 0; j < 8; j++) {
      tmp <<= 1;  //shift the tmp because alread have the LSB of num
      tmp |= letter[i] & 1; // putting the set bits of num
      letter[i] >>= 1;      
      count--;
    }
    res[i] = tmp;
  }
  return res;
}

void inverse_matrix_tab(uint8_t** matrix_tab, uint8_t size)
{
  uint8_t res[8];
  uint8_t* letter;
  uint8_t tmp;
  uint8_t count;
  for (int m = 0; m < size; m++)
    {
      letter = matrix_tab[m];
      tmp = 0;
      count = 0;

  for(uint8_t i = 0; i < 8; i++) {
    count = 7;
    for(uint8_t j = 0; j < 8; j++) {
      tmp <<= 1;  //shift the tmp because alread have the LSB of num
      tmp |= letter[i] & 1; // putting the set bits of num
      letter[i] >>= 1;
      count--;
    }
    res[i] = tmp;
  }


      for (int i = 0; i < 8; i++)
      {
	letter[i] = res[i];
      }
    }
}


uint8_t* turn_letter(uint8_t* res, uint8_t* letter)
{
    for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
	res[i] = (res[i] << 1) | ((letter[j] >> (7 - i)) & 0x01);
      }
    }
  return res;
}

void turn_matrix_tab(uint8_t** matrix_tab, uint8_t size)
{
  uint8_t res[8];
  uint8_t* letter;
  for (int m = 0; m < size; m++)
    {
      letter = matrix_tab[m];
    for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
	res[i] = (res[i] << 1) | ((letter[j] >> (7 - i)) & 0x01);
      }
    }
    for (int i = 0; i < 8; i++)
      {
	letter[i] = res[i];
      }
    }
}

void decal_letter_tab(uint8_t** matrix_tab, uint8_t size)
{
  uint8_t res[8];
  uint8_t* letter;
  for (int m = 0; m < size; m++)
    {
      letter = matrix_tab[m];
    for(int i = 1; i < 8; i++) {
      /* for(int j = 0; j < 8; j++) { */
	res[i] = letter[i -  1];
      /* } */
    }
    for (int i = 0; i < 8; i++)
      {
	letter[i] = res[i];
      }
    }
}

void decal_letter_tab_2(uint8_t** matrix_tab, uint8_t size)
{
  uint8_t res[8];
  uint8_t* letter;
  for (int m = 0; m < size; m++)
    {
      letter = matrix_tab[m];
    for(int i = 0; i < 8 - 1; i++) {
      res[i] = letter[i +  1];
    }
    res[7] = 0;
    for (int i = 0; i < 8; i++)
      {
	letter[i] = res[i];
      }
    }
}

void decal_1_left(uint8_t* strings[8], uint8_t size)
{
  uint8_t* res[18];
  uint8_t letter0[8] = {0, };
  uint8_t letter1[8] = {0, };
  uint8_t letter2[8] = {0, };
  uint8_t letter3[8] = {0, };
  uint8_t letter4[8] = {0, };
  uint8_t letter5[8] = {0, };
  uint8_t letter6[8] = {0, };
  uint8_t letter7[8] = {0, };
  uint8_t letter8[8] = {0, };
  uint8_t letter9[8] = {0, };
  uint8_t letter10[8] = {0, };
  uint8_t letter11[8] = {0, };
  uint8_t letter12[8] = {0, };
  uint8_t letter13[8] = {0, };
  uint8_t letter14[8] = {0, };
  uint8_t letter15[8] = {0, };
  uint8_t letter16[8] = {0, };
  uint8_t letter17[8] = {0, };

  res[0] = letter0;
  res[1] = letter1;
  res[2] = letter2;
  res[3] = letter3;
  res[4] = letter4;
  res[5] = letter5;
  res[6] = letter6;
  res[7] = letter7;
  res[8] = letter8;
  res[9] = letter9;
  res[10] = letter10;
  res[11] = letter11;
  res[12] = letter12;
  res[13] = letter13;
  res[14] = letter14;
  res[15] = letter15;
  res[16] = letter16;
  res[17] = letter17;

  if (size == 0)
    return;
  for (uint8_t i = 0; i < size; i++)
    {
      for (uint8_t j = 0; j < 8; j++)
	res[i][j] = strings[i][j] << 1;
    }
  for (uint8_t i = 0; i < size; i++)
    {
      for (uint8_t j = 0; j < 8; j++)
	{
	  if (i == 0)
	    res[i][j] = res[i][j] | ((strings[size - 1][j] & 0b10000000) >> 7);
	  else
	    res[i][j] = res[i][j] | ((strings[i - 1][j] & 0b10000000) >> 7);
	}
    }
  for (uint8_t i = 0; i < size; i++)
    {
      for (uint8_t j = 0; j < 8; j++)
        strings[i][j] = res[i][j];
    }
}

void decal_1_right(uint8_t* strings[8], uint8_t size)
{
  uint8_t* res[18];
  uint8_t letter0[8] = {0, };
  uint8_t letter1[8] = {0, };
  uint8_t letter2[8] = {0, };
  uint8_t letter3[8] = {0, };
  uint8_t letter4[8] = {0, };
  uint8_t letter5[8] = {0, };
  uint8_t letter6[8] = {0, };
  uint8_t letter7[8] = {0, };
  uint8_t letter8[8] = {0, };
  uint8_t letter9[8] = {0, };
  uint8_t letter10[8] = {0, };
  uint8_t letter11[8] = {0, };
  uint8_t letter12[8] = {0, };
  uint8_t letter13[8] = {0, };
  uint8_t letter14[8] = {0, };
  uint8_t letter15[8] = {0, };
  uint8_t letter16[8] = {0, };
  uint8_t letter17[8] = {0, };

  res[0] = letter0;
  res[1] = letter1;
  res[2] = letter2;
  res[3] = letter3;
  res[4] = letter4;
  res[5] = letter5;
  res[6] = letter6;
  res[7] = letter7;
  res[8] = letter8;
  res[9] = letter9;
  res[10] = letter10;
  res[11] = letter11;
  res[12] = letter12;
  res[13] = letter13;
  res[14] = letter14;
  res[15] = letter15;
  res[16] = letter16;
  res[17] = letter17;

  if (size == 0)
    return;
  for (uint8_t i = 0; i < size; i++)
    {
      for (uint8_t j = 0; j < 8; j++)
	res[i][j] = strings[i][j] >> 1;
    }
  for (uint8_t i = 0; i < size; i++)
    {
      for (uint8_t j = 0; j < 8; j++)
	{
	  if (i == size - 1)
	    res[i][j] = res[i][j] | ((strings[0][j] & 0b00000001) << 7);
	  else
	    res[i][j] = res[i][j] | ((strings[i + 1][j] & 0b000000001) << 7);
	}
    }
  for (uint8_t i = 0; i < size; i++)
    {
      for (uint8_t j = 0; j < 8; j++)
        strings[i][j] = res[i][j];
    }
}

// a finir de coder
/* void sideway_left(uint8_t* strings[8], uint8_t size) */
/* { */
/*   uint8_t res[size][8]; */

/*   if (size == 0) */
/*     return; */
/*   for (uint8_t i = 0; i < size; i++) */
/*     { */
/*       for (uint8_t j = 0; j < 8; j++) */
/* 	{ */
/* 	  if (j == 8) */
/* 	    { */
/* 	      if (i == size) */
/* 		res[i][j] = strings[0][0]; */
/* 	      else */
/* 		res[i][j] = strings[i + 1][0]; */
/* 	    } */
/* 	  else */
/* 	    res[i][j] = strings[i][j + 1]; */
/* 	} */
/*     } */
/*   /\* for (uint8_t i = 0; i < size; i++) *\/ */
/*   /\*   { *\/ */
/*   /\*     for (uint8_t j = 0; j < 8; j++) *\/ */
/*   /\* 	{ *\/ */
/*   /\* 	  if (i + 1 >= size) *\/ */
/*   /\* 	      res[i][j] = res[i][j] | (strings[0][j] & 0b10000000); *\/ */
/*   /\* 	  else *\/ */
/*   /\* 	    res[i][j] = res[i][j] | (strings[i + 1][j] & 0b10000000); *\/ */
/*   /\* 	} *\/ */
/*   /\*   } *\/ */
/*   for (uint8_t i = 0; i < size; i++) */
/*     { */
/*       for (uint8_t j = 0; j < 8; j++) */
/*         strings[i][j] = res[i][j]; */
/*     } */
/* } */

void fill_matrix_tab(uint8_t** matrix_tab, uint8_t* string, uint8_t size)
{
  for (uint8_t i = 0; i < size; i++)
    {
      for (uint8_t j = 0; j < 8; j++)
	matrix_tab[i][j] = MAX7219_Dot_Matrix_font[string[i] - 0x20][j];
    }
}
