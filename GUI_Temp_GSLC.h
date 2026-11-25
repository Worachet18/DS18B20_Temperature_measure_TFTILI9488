//<File !Start!>
// FILE: [GUI_Temp_GSLC.h]
// Created by GUIslice Builder version: [0.17.b34]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XCheckbox.h"
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if !defined(DRV_DISP_TFT_ESPI)
  #error E_PROJECT_OPTIONS tab->Graphics Library should be Adafruit_GFX
#endif
#include <TFT_eSPI.h>
#include "NotoMono14pt7b.h"
#include "NotoMono24pt7b.h"
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_MAIN};
enum {E_ELEM_RADIO1,E_ELEM_RADIO2,E_ELEM_RADIO3,E_ELEM_TEXT1
      ,E_ELEM_TEXT10,E_ELEM_TEXT11,E_ELEM_TEXT12,E_ELEM_TEXT13
      ,E_ELEM_TEXT14,E_ELEM_TEXT15,E_ELEM_TEXT2,E_ELEM_TEXT3
      ,E_ELEM_TEXT4,E_ELEM_TEXT5,E_ELEM_TEXT6};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN5X8,E_FREEMONOBOLD12,E_FREEMONOBOLD24,E_NOTOMONO14
      ,E_NOTOMONO24,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                1

#define MAX_ELEM_PG_MAIN 15 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsXCheckbox                m_asXRadio1;
gslc_tsXCheckbox                m_asXRadio2;
gslc_tsXCheckbox                m_asXRadio3;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pElemRBRadioButton;
extern gslc_tsElemRef* m_pElemRBRadioButton2;
extern gslc_tsElemRef* m_pElemRBRadioButton2_3;
extern gslc_tsElemRef* m_pElemStatusText;
extern gslc_tsElemRef* t1;
extern gslc_tsElemRef* t2;
extern gslc_tsElemRef* t3;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREEMONOBOLD12,GSLC_FONTREF_PTR,&FreeMonoBold12pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREEMONOBOLD24,GSLC_FONTREF_PTR,&FreeMonoBold24pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_NOTOMONO14,GSLC_FONTREF_PTR,&NotoMono14pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_NOTOMONO24,GSLC_FONTREF_PTR,&NotoMono24pt7b,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_WHITE);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
  
  // Create E_ELEM_TEXT1 runtime modifiable text
  static char m_sDisplayText1[6] = "23.8";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT1,E_PG_MAIN,(gslc_tsRect){100,100,150,50},  //new version
  // pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT1,E_PG_MAIN,(gslc_tsRect){100,60,150,50},  //old version
    (char*)m_sDisplayText1,6,E_FREEMONOBOLD24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  t1 = pElemRef;
  
  // Create E_ELEM_TEXT2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT2,E_PG_MAIN,(gslc_tsRect){10,70,90,30},  //new version
  // pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT2,E_PG_MAIN,(gslc_tsRect){10,50,90,30},  //old version
    (char*)"Temp 1",0,E_FREEMONOBOLD12);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT3,E_PG_MAIN,(gslc_tsRect){10,170,90,30},  //new version
  // pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT3,E_PG_MAIN,(gslc_tsRect){10,120,90,30},  //old version
    (char*)"Temp 2",0,E_FREEMONOBOLD12);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT4 runtime modifiable text
  static char m_sDisplayText4[6] = "98.8";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT4,E_PG_MAIN,(gslc_tsRect){100,200,150,50},  //new version
  // pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT4,E_PG_MAIN,(gslc_tsRect){100,150,150,50},  //old version
    (char*)m_sDisplayText4,6,E_FREEMONOBOLD24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  t2 = pElemRef;
  
  // Create E_ELEM_TEXT5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT5,E_PG_MAIN,(gslc_tsRect){10,270,90,30},  //new version
  // pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT5,E_PG_MAIN,(gslc_tsRect){10,220,90,30},  //old version
    (char*)"Temp 3",0,E_FREEMONOBOLD12);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT6 runtime modifiable text
  static char m_sDisplayText6[6] = "78.8";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT6,E_PG_MAIN,(gslc_tsRect){100,300,150,50},  //new version
  // pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT6,E_PG_MAIN,(gslc_tsRect){100,250,150,50},  //old version
    (char*)m_sDisplayText6,6,E_FREEMONOBOLD24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  t3 = pElemRef;
  
  // Create E_ELEM_TEXT10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT10,E_PG_MAIN,(gslc_tsRect){60,20,206,21},  //new version
  // pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT10,E_PG_MAIN,(gslc_tsRect){20,20,206,21},  //old version
    (char*)"Trai Mushroom",0,E_NOTOMONO14);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE_DK2);
  
  // Create radio button E_ELEM_RADIO1
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO1,E_PG_MAIN,&m_asXRadio1,
    (gslc_tsRect){240,100,10,10},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_ORANGE,false);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_BLACK,GSLC_COL_WHITE);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRBRadioButton = pElemRef;
  
  // Create radio button E_ELEM_RADIO2
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO2,E_PG_MAIN,&m_asXRadio2,
    (gslc_tsRect){240,200,10,10},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_ORANGE,false);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRBRadioButton2 = pElemRef;
  
  // Create radio button E_ELEM_RADIO3
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO3,E_PG_MAIN,&m_asXRadio3,
    (gslc_tsRect){240,300,10,10},true,GSLCX_CHECKBOX_STYLE_ROUND,GSLC_COL_ORANGE,false);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRBRadioButton2_3 = pElemRef;
  
  // Create E_ELEM_TEXT11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT11,E_PG_MAIN,(gslc_tsRect){250,110,25,29},
    (char*)"C",0,E_FREEMONOBOLD24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT12,E_PG_MAIN,(gslc_tsRect){250,210,25,29},
    (char*)"C",0,E_FREEMONOBOLD24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT13,E_PG_MAIN,(gslc_tsRect){250,310,25,29},
    (char*)"C",0,E_FREEMONOBOLD24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT14 runtime modifiable text
  static char m_sDisplayText14[11] = "OFFLINE";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT14,E_PG_MAIN,(gslc_tsRect){80,380,190,35},  //new version
  // pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT14,E_PG_MAIN,(gslc_tsRect){80,280,190,35},  //old version
    (char*)m_sDisplayText14,11,E_NOTOMONO24);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN_DK4);
  m_pElemStatusText = pElemRef;
  
  // Create E_ELEM_TEXT15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT15,E_PG_MAIN,(gslc_tsRect){10,460,198,8},
    (char*)"TECHVISION AND ROBOTICS CO., LTD.",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
//<InitGUI !End!>

//<Startup !Start!>
  gslc_GuiRotate(&m_gui, 0);
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
