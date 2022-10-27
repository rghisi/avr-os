#ifndef HD44780_SETTINGS_H_INCLUDED
#define HD44780_SETTINGS_H_INCLUDED
/*
||
||  Filename:	 		HD44780_Settings.h
||  Title: 			    HD44780 Driver Settings
||  Author: 			Efthymios Koktsidis
||	Email:				efthymios.ks@gmail.com
||  Compiler:		 	AVR-GCC
||	Description:
||	Settings for the HD44780 driver. Pick a size and the
||	desirable pins. 16x1 needs testing.
||
||	Size	Code	|	Size	Code	      |	Size	Code	  |	Size	Code	  |
||------------------------------------------------------------------|
||	8x1 -	801 	| *	16x1 -	1601 *	|	20x1 -	2001 	|	40x1 -	4001	|
||	8x2 -	802		|	16x2 -	1602 	    |	20x2 -	2002 	|	40x2 -	4002 	|
||					    |	16x4 -	1604 	    |	20x4 -	2004 	|					      |
||
||*If LCD size is 16x1, choose variant A or B
||	Type	Row DDRAM Address			Details
||	Α		0x00->0x0F					Row uses consequtive block addresses.
||	Β		0x00->0x07 + 0x40->0x47		Row is split into two sections.
||
*/

//----- Configuration --------------------------//
//LCD size
#define LCD_Size	802

//If LCD size is 16x1, define type A or B
#define LCD_Type	A

//LCD pins			PORT, PIN
#define LCD_D4		B, 1
#define LCD_D5		B, 2
#define LCD_D6		B, 3
#define LCD_D7		B, 4
#define LCD_RS		F, 7
#define LCD_RW      F, 6
#define LCD_EN		F, 5
//----------------------------------------------//
#endif