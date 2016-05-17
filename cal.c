#include<stdlib.h>
#include<stdio.h>

int day_of_year(int year, int month, int day, char (*daytab)[13]){
  int i, leap;

  leap = year % 4 == 0 && year % 100 != 0 && year % 400 != 0;
  for(i=0; i<month; i++){
    day += daytab[leap][i];
  }

  return day;
}

void month_day(int year, int yearDay, int *pmonth, int *pday, char daytab[][13]){
  int i, leap;

  leap = year % 4 == 0 && year % 100 != 0 && year % 400 != 0;
  for(i=1; yearDay > daytab[leap][i]; i++){
    yearDay -= daytab[leap][i];
  }

  *pmonth = i;
  *pday = yearDay;
}

int main(){
 char daytab[2][13] = {
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
 };

  printf("%d\n", day_of_year(2016, 04, 06, daytab));

  int month;
  int day;

  month_day(2016, 60, &month, &day, daytab);
  printf("%d/%d\n", day, month);

}
