/*This file is part of cwci.

Cwci is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Cwci is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Cwci.  If not, see <http://www.gnu.org/licenses/>.*/

#include "libwc.h"
#include "libwc.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>
#include <sys/stat.h>

void wc_engine(int argc, char *argv[])
{
  char current_char;
  bool word_flag = false;
  int word_len_counter = 0;
  int line_len_counter = 0;
  int ch;
    FILE *file_to_read;
    if(!(file_to_read = fopen(argv[0], "r")))
    {
      if(english_selected)
        fprintf(stderr, "%s: no such file \"%s\"\n", EXEC_NAME, argv[0]);
      else
        fprintf(stderr, "%s: нет такого файла \"%s\"\n", EXEC_NAME, argv[0]);
      exit(3);
    }
  if(bytes_opt_selected)
  {
    struct stat buff;
    stat(argv[0], &buff);
    bytes_counter = buff.st_size;
  }
  /*for(int i = 0; i < argc; i++){
    char ch[] = argv[i];
    for(int j = 0; ch[j] != '\0'; i++)  }*/
  if(greeting_opt_selected)
    greeting();
  if(help_opt_selected)
    print_help();
  while((ch = fgetc(file_to_read)) != EOF)
  {
    current_char = ch;

    if(!word_flag && words_opt_selected)
    {
      word_flag = true;
      if(current_char != ' ')
        word_len_counter++;
    }
    else if(word_flag && current_char != ' ' && current_char != '\n' && current_char != '\t' && words_opt_selected)
    {
      word_len_counter++;
    }
    if(word_flag && current_char == ' ' && words_opt_selected && word_len_counter == 0) //exception for several spaces in a row
    {
      word_flag = false;
      word_len_counter = 0;
    }
    if(word_flag && (current_char == ' ' || current_char == '\n' || current_char == '\t') && words_opt_selected)
    {
      words_counter++;
      word_flag = false;
      word_len_counter = 0;
    }

    if(isdigit(current_char) && digit_opt_selected)
    {
        digit_counter++;
    }
    if(chars_opt_selected)
    {
      chars_counter++;
    }
    if(max_line_len_selected)
    {
      line_len_counter++;
    }
    if(spaces_opt_selected && current_char == ' ')
    {
        spaces_counter++;
    }
    if(lines_opt_selected && current_char == '\n')
    {
      lines_counter++;
      if(max_line_len_selected)
      {
        if(max_line_length < line_len_counter)
          max_line_length = line_len_counter;
        line_len_counter = 0;
      }
    }
  }
  if(!standard_input_selected)
    fclose(file_to_read);
//else
  //free(str_to_read);
}
