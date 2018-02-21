#ifndef __UNISTYLE__H__
#define __UNISTYLE__H__

#include <yaml.h>

enum EType {
  DOCUMENT,
  TITLE,
  AUTHOR,
  AFFILIATION,
  ABSTRACT,
  H1,
  H2,
  H3,
  H4,
  H5,
  H6,
  TABLE,
  CODE,
  PARAGRAPH,
  LIST,
  ENUMERATE,
  QUOTE,
  E_NONE
} typedef EType;

enum PType {
  COLOR,
  BACKGROUND,
  FONT,
  FONT_SIZE,
  FONT_FAMILY,
  FONT_NAME,
  FONT_WEIGHT,
  TEXT,
  TEXT_STYLE,
  TEXT_ALIGN,
  MARGIN,
  MARGIN_TOP,
  MARGIN_LEFT,
  MARGIN_BOTTOM,
  MARGIN_RIGHT,
  COLUMNS,
  P_NONE,
} typedef PType;

enum VType{
  STRING,
  RGB,
  RGBA,
  HASHC,
  NUMBER,
  SIZE,
  CATEGORY
} typedef VType;

struct Value {
  VType           type;
  void           *raw;
} typedef Value;

struct Preference {
  PType           type;
  Value          *value;
} typedef  Preference;

struct PrefList {
  Preference     *preference;
  void           *next;
  void           *prev;
} typedef PrefList;


struct Element{
  EType           type;
  PrefList       *list;
} typedef Element;

struct ElemList{
  Element        *el;
  void           *next;
  void           *prev;
} typedef ElemList;

struct Style {
  ElemList       *list;
} typedef Style;


EType       elem_type_parse (char          *val);
PType       pref_type_parse (char          *val);

Value      *value_new       (VType          type,
                             void          *raw);
void        value_free      (Value         *val);

Preference *preference_new  (PType          type,
                             Value         *val);
void        preference_free (Preference    *pref);
void        preference_print(Preference   *pref);

PrefList   *pref_list_new   (void);
void        pref_list_free  (PrefList      *list);
PrefList   *pref_list_add   (PrefList      *list,
                             Preference    *pref);

Element    *element_new     (EType          type);
void        element_free    (Element       *elem);
void        element_print   (Element       *elem);

ElemList   *elem_list_new   (void);
void        elem_list_free  (ElemList      *elem_list);
ElemList   *elem_list_add   (ElemList      *elem_list,
                             Element       *elem);

void        style_free      (Style         *style);
Style      *style_new       (void);
void        style_print     (Style         *style);


void        parse_element   (Style         *style,
                             yaml_parser_t *parser,
                             yaml_token_t  *token);

PrefList   *parse_preference (PrefList     *list,
                             yaml_parser_t *parser,
                             yaml_token_t  *token);


Style      *parse           (char          *data);

#endif