/*
    File: dates.c
    Author: Ashley Manson
 
    Reformats inputted dates to a standard form.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {false, true} bool;

/* Test if a char is seperator or not */
bool is_sep (char sep) {
   if (isalpha(sep) || isdigit(sep)) {
      return false;
   }
   return true;
}

/* Check if a "string" is made up of all digits or not */
bool is_all_digit (char *string) {
   int letter;
   for (letter = 0; letter < strlen(string); letter++) {
      if (!isdigit(string[letter])) return false;
   }
   return true;
}

/* Check if a "string" is made up of all alphabetical letters or not */
bool is_all_alpha(char *string) {
   int letter;
   for (letter = 0; letter < strlen(string); letter++) {
      if (!isalpha(string[letter])) return false;
   }
   return true;
}

char *get_sub_string (char *string, int position, int length) {

   int letter;
   char *sub_string;
 
   sub_string = malloc(length + 1);
	
   if (sub_string == NULL) {
      fprintf(stderr, "Error! :: Unable to allocate memory.");
      exit(EXIT_FAILURE);
   }

   for (letter = 0; letter < position - 1; letter++) string++;
 
   for (letter = 0; letter < length; letter++) {
      *(sub_string + letter) = *string;
      string++;   
   }
 
   *(sub_string + letter) = '\0';
 
   return sub_string;
}

int check (char *date) {

   int length_date = strlen(date);
   int letter;

   bool sep_passed;
   char first_sep;
   char sec_sep;
   int first_sep_loc;
   int sec_sep_loc;
	
   bool year_is_leap;
   bool month_is_digit;

   char *day;
   char *month;
   char *year;
	
   int day_int;
   int month_int;
   int year_int;
   char *mon_to_print;

   sep_passed = false;
   letter = 1;

   while (!sep_passed) {
      if (letter >= length_date) {
         printf("%s - First seperator not found.\n", date);
         return -1;
      }
      first_sep = date[letter++];
      if (is_sep(first_sep)) {
         sep_passed = true;
         first_sep_loc = letter;
      }
   }
	
   sep_passed = false;
   letter = 3;

   while (!sep_passed) {
      if (letter >= length_date) {
         printf("%s - Second seperator not found.\n", date);
         return -1;
      }
      sec_sep = date[letter++];
      if (is_sep(sec_sep)) {
         sep_passed = true;
         sec_sep_loc = letter;
      }
   }
	
   if (first_sep != sec_sep) {
      printf("%s - Seperators do not match.\n", date);
      return -1;
   }
   	
   day = get_sub_string(date, 0, first_sep_loc - 1);
   month = get_sub_string(date, first_sep_loc + 1, (sec_sep_loc-first_sep_loc) - 1);
   year = get_sub_string(date, sec_sep_loc + 1, length_date-sec_sep_loc);
   
   day_int = atoi(day);
   month_int = atoi(month);
   year_int = atoi(year);

   if (!is_all_digit(day)) {
      printf("%s - Day is not valid.\n", date);
      return -1;
   }
   if (!is_all_digit(year)) {
      printf("%s - Year is not valid.\n", date);
      return -1;
   }
   if (!is_all_digit(month) && !is_all_alpha(month)) {
      printf("%s - Month is not valid.\n", date);
      return -1;
   }

   if (day_int < 1 || day_int > 31) {
      printf("%s - Day is out of range.\n", date);
      return -1;
   }
   if (month_int < 0 || month_int > 12) {
      printf("%s - Month is out of range.\n", date);
      return -1;
   }
   if (year_int > 3000 || (year_int < 1753 && year_int > 99) || year_int < 0) {
      printf("%s - Year is out of range.\n", date);
      return -1;
   }
   if (strlen(year) > 4) {
      printf("%s - Year is not valid.\n", date);
      return -1;
   }
   if (strlen(month) > 2 && is_all_digit(month)) {
      printf("%s - Month is not valid.\n", date);
      return -1;      
   }
   
   if (month_int == 0) month_is_digit = false;
   else month_is_digit = true;

   if (strlen(year) == 2) {
      if (year_int > 49) year_int = 1900 + year_int;
      else year_int = 2000 + year_int;
   }
   if (year_int % 400 == 0) year_is_leap = true;
   else if (year_int % 100 == 0) year_is_leap = false;
   else if (year_int % 4 == 0) year_is_leap = true;
   else year_is_leap = false;

   if (month_is_digit) {
      switch (month_int) {
      case 1:
         mon_to_print = "Jan";
         break;
      case 2:
         mon_to_print = "Feb";
         break;
      case 3:
         mon_to_print = "Mar";
         break;
      case 4:
         mon_to_print = "Apr";
         break;
      case 5:
         mon_to_print = "May";
         break;
      case 6:
         mon_to_print = "Jun";
         break;
      case 7:
         mon_to_print = "Jul";
         break;
      case 8:
         mon_to_print = "Aug";
         break;
      case 9:
         mon_to_print = "Sep";
         break;
      case 10:
         mon_to_print = "Oct";
         break;
      case 11:
         mon_to_print = "Nov";
         break;
      case 12:
         mon_to_print = "Dec";
         break;
      }
   }
   else {
      if (strcmp(month, "jan") == 0 || strcmp(month, "JAN") == 0 || strcmp(month, "Jan") == 0) {
         mon_to_print = "Jan";
         month_int = 1;
      }
      else if (strcmp(month, "feb") == 0 || strcmp(month, "FEB") == 0 || strcmp(month, "Feb") == 0) {
         mon_to_print = "Feb";
         month_int = 2;
      }
      else if (strcmp(month, "mar") == 0 || strcmp(month, "MAR") == 0 || strcmp(month, "Mar") == 0) {
         mon_to_print = "Mar";
         month_int = 3;
      }
      else if (strcmp(month, "apr") == 0 || strcmp(month, "APR") == 0 || strcmp(month, "Apr") == 0) {
         mon_to_print = "Apr";
         month_int = 4;
      }
      else if (strcmp(month, "may") == 0 || strcmp(month, "MAY") == 0 || strcmp(month, "May") == 0) {
         mon_to_print = "May";
         month_int = 5;
      }
      else if (strcmp(month, "jun") == 0 || strcmp(month, "JUN") == 0 || strcmp(month, "Jun") == 0) {
         mon_to_print = "Jun";
         month_int = 6;
      }
      else if (strcmp(month, "jul") == 0 || strcmp(month, "JUL") == 0 || strcmp(month, "Jul") == 0) {
         mon_to_print = "Jul";
         month_int = 7;
      }
      else if (strcmp(month, "aug") == 0 || strcmp(month, "AUG") == 0 || strcmp(month, "Aug") == 0) {
         mon_to_print = "Aug";
         month_int = 8;
      }
      else if (strcmp(month, "sep") == 0 || strcmp(month, "SEP") == 0 || strcmp(month, "Sep") == 0) {
         mon_to_print = "Sep";
         month_int = 9;
      }
      else if (strcmp(month, "oct") == 0 || strcmp(month, "OCT") == 0 || strcmp(month, "Oct") == 0) {
         mon_to_print = "Oct";
         month_int = 10;
      }
      else if (strcmp(month, "nov") == 0 || strcmp(month, "NOV") == 0 || strcmp(month, "Nov") == 0) {
         mon_to_print = "Nov";
         month_int = 11;
      }
      else if (strcmp(month, "dec") == 0 || strcmp(month, "DEC") == 0 || strcmp(month, "Dec") == 0) {
         mon_to_print = "Dec";
         month_int = 12;
      }
      else {
         printf("%s - Month is not valid.\n", date);
         return -1;
      }
   }
   switch (day_int) {
   case 29:
      if (month_int == 2 && !year_is_leap) {
         printf("%s - Day is out of range.\n", date);
         return -1;
      }
      break;
   case 30:
      if (month_int == 2) {
         printf("%s - Day is out of range.\n", date);
         return -1;
      }
      break;
   case 31:
      if (month_int == 2 || 
          month_int == 4 || 
          month_int == 6 || 
          month_int == 9 || 
          month_int == 11) {
         printf("%s - Day is out of range.\n", date);
         return -1;
      }
   }
   printf("%02d %s %d\n", day_int, mon_to_print, year_int);
	
   free(day);
   free(month);
   free(year);

   return 0;
}

int main (void) {

   char input[15];
   char *date;

   for (;;) {
      /* Done this way to stop infinite loop */
      date = fgets(input, sizeof(input), stdin);
      if (date == NULL) break;
      strtok(date, "\n");
      check(date);
   }
	
   return 0;
}
