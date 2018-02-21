#include "unistyle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Value *
value_new(VType type,
          void *raw) {
  Value *val = malloc(sizeof(Value));
  val->raw = raw;
  val->type = type;

  return val;
}

void value_free(Value *val) {
  free(val->raw);
  free(val);
}

void
value_print (Value         *val)
{
  if (val->type == CATEGORY)
  {
    printf("\n");
    PrefList * el = (PrefList*)val->raw;
    for (;el!=NULL; el = el->next)
    {
      printf("    ");
      preference_print(el->preference);
    }
  } else {
    printf("%s", (char*)val->raw);
    printf("\n");
  }
}

Preference *
preference_new(PType type,
               Value *val) {
  Preference *pref = malloc(sizeof(Preference));
  pref->type = type;
  pref->value = val;
  return pref;
}

void preference_free(Preference *pref) {
  value_free(pref->value);
  free(pref);
}

void
preference_print(Preference   *pref)
{
  printf(" - ");
  switch(pref->type)
  {
  case COLOR:
    printf("color");
    break;
  case BACKGROUND:
    printf("background");
    break;
  case FONT:
    printf("font");
    break;
  case COLUMNS:
    printf("columns");
    break;
  case MARGIN:
    printf("margin");
    break;
  case FONT_FAMILY:
    printf("font-family");
    break;
  case FONT_SIZE:
    printf("font-size");
    break;
  case FONT_NAME:
    printf("font-name");
    break;
  case FONT_WEIGHT:
    printf("font-weight");
    break;
  case MARGIN_BOTTOM:
    printf("margin-bottom");
    break;
  case MARGIN_LEFT:
    printf("margin-left");
    break;
  case MARGIN_RIGHT:
    printf("margin-right");
    break;
  case MARGIN_TOP:
    printf("margin-top");
    break;
  case TEXT:
    printf("text");
    break;
  case TEXT_ALIGN:
    printf("text-align");
    break;
  case TEXT_STYLE:
    printf("text-style");
    break;
  default:
    printf("S<%d>", pref->type);
  }
  printf(": ");
  value_print(pref->value);
}

PrefList *pref_list_new(void) {
  PrefList *el = malloc(sizeof(PrefList));
  el->next = NULL;
  el->preference = NULL;
  el->prev = NULL;
  return el;
}

void pref_list_free(PrefList *list) {
  if(list) {
    if(list->next) {
      pref_list_free(list->next);
      preference_free(list->preference);
      free(list);
    }
  }
}

PrefList *pref_list_add(PrefList *list,
                        Preference *pref) {
  if(list) {

    if(list->next) {
      pref_list_add(list->next, pref);
    }
    else {
      PrefList *el = pref_list_new();
      el->preference = pref;
      el->prev = list;
      list->next = el;
    }
    return list;
  }
  else {
    list = pref_list_new();
    list->preference = pref;
    return list;
  }
}

Element *
element_new(EType type) {
  Element *el = malloc(sizeof(Element));
  el->type = type;
  el->list = NULL;
  return el;
}

void element_free(Element *elem) {
  pref_list_free(elem->list);
  free(elem);
}

void element_print(Element *elem) {
  switch(elem->type) {
  case DOCUMENT:
    printf("Document");
    break;
  case H1:
    printf("H1");
    break;
  case H2:
    printf("H2");
    break;
  case H3:
    printf("H3");
    break;
  case H4:
    printf("H4");
    break;
  case H5:
    printf("H5");
    break;
  case H6:
    printf("H6");
    break;
  case TITLE:
    printf("Title");
    break;
  case AUTHOR:
    printf("Author");
    break;
  case AFFILIATION:
    printf("Affiliation");
    break;
  case ABSTRACT:
    printf("Abstract");
    break;
  case TABLE:
    printf("Table");
    break;
  case CODE:
    printf("Code");
    break;
  case PARAGRAPH:
    printf("Paragraph");
    break;
  case LIST:
    printf("List");
    break;
  case ENUMERATE:
    printf("Enumerate");
    break;
  case QUOTE:
    printf("Quote");
    break;
  default:
    printf("E<%d>", elem->type);
  }
  printf(":\n");
  PrefList * el;
  for (el = elem->list; el != NULL; el = el->next)
  {
    preference_print(el->preference);
  }
}

ElemList *
elem_list_new(void) {
  ElemList *el = malloc(sizeof(ElemList));
  el->next = NULL;
  el->prev = NULL;
  el->el = NULL;
  return el;
}

void elem_list_free(ElemList *list) {
  if(list->next) {
    elem_list_free(list->next);
  }
  free(list);
}

ElemList *
elem_list_add(ElemList *list,
              Element *elem) {
  if(list) {
    if(list->next) {
      elem_list_add(list->next, elem);
    }
    else {
      ElemList *el = elem_list_new();
      list->next = el;
      el->el = elem;
      el->prev = list;
    }
    return list;
  }
  else {
    list = elem_list_new();
    list->el = elem;
    return list;
  }
}

void style_free(Style *st) {
  if(st->list) {
    style_free(st);
  }
}

Style *
style_new(void) {
  Style *style = malloc(sizeof(Style));
  style->list = NULL;
  return style;
}

void style_print(Style *style) {
  ElemList *el;
  for(el = style->list; el != NULL; el = el->next) {
    element_print(el->el);
  }
}


EType elem_type_parse(char *val) {
  if(strcmp(val, "document") == 0)
    return DOCUMENT;
  if(strcmp(val, "title") == 0)
    return TITLE;
  if(strcmp(val, "author") == 0)
    return AUTHOR;
  if(strcmp(val, "affiliation") == 0)
    return AFFILIATION;
  if(strcmp(val, "abstract") == 0)
    return ABSTRACT;
  if(strcmp(val, "h1") == 0)
    return H1;
  if(strcmp(val, "h2") == 0)
    return H2;
  if(strcmp(val, "h3") == 0)
    return H3;
  if(strcmp(val, "h4") == 0)
    return H4;
  if(strcmp(val, "h5") == 0)
    return H5;
  if(strcmp(val, "h6") == 0)
    return H6;
  if(strcmp(val, "quote") == 0)
    return QUOTE;
  if(strcmp(val, "list") == 0)
    return LIST;
  if(strcmp(val, "code") == 0)
    return CODE;

  return E_NONE;
}

PType pref_type_parse(char *val) {
  if(!strcmp(val, "color"))
    return COLOR;
  if(!strcmp(val, "background"))
    return BACKGROUND;
  if(!strcmp(val, "font"))
    return FONT;
  if(!strcmp(val, "size") || !strcmp(val, "font-size"))
    return FONT_SIZE;
  if(!strcmp(val, "family") || !strcmp(val, "font-family"))
    return FONT_FAMILY;
  if(!strcmp(val, "name") || !strcmp(val, "font-name"))
    return FONT_NAME;
  if(!strcmp(val, "weight") || !strcmp(val, "font-weight"))
    return FONT_WEIGHT;
  if(!strcmp(val, "text"))
    return TEXT;
  if(!strcmp(val, "style") || !strcmp(val, "text-style"))
    return TEXT_STYLE;
  if(!strcmp(val, "align") || !strcmp(val, "text-align"))
    return TEXT_ALIGN;
  if(!strcmp(val, "margin"))
    return MARGIN;
  if(!strcmp(val, "top") || !strcmp(val, "margin-top"))
    return MARGIN_TOP;
  if(!strcmp(val, "left") || !strcmp(val, "margin-left"))
    return MARGIN_LEFT;
  if(!strcmp(val, "bottom") || !strcmp(val, "margin-bottom"))
    return MARGIN_BOTTOM;
  if(!strcmp(val, "right") || !strcmp(val, "margin-right"))
    return MARGIN_RIGHT;
  if(!strcmp(val, "columns"))
    return COLUMNS;

  return P_NONE;
}
