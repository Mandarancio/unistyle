#include "unistyle.h"

#include <stdlib.h>
#include <yaml.h>


Value*
parse_value(char *string)
{
  return value_new(STRING, string);
}

Value*
parse_category(yaml_parser_t *parser,
               yaml_token_t  *token)
{
   PrefList * list = NULL;
   do{
     yaml_parser_scan(parser, token);
     switch (token->type)
     {
     case YAML_KEY_TOKEN:
       list = parse_preference(list, parser, token);
       break;
     default:
       break;
     }
   } while (token->type != YAML_BLOCK_END_TOKEN);
   if (list)
   {
     return value_new(CATEGORY, list);
   }

   return NULL;
}

PrefList*
parse_preference(PrefList *list,
                 yaml_parser_t *parser,
                 yaml_token_t  *token)
{
  yaml_parser_scan(parser, token);
  if (token->type != YAML_SCALAR_TOKEN)
  {
    return NULL;
  }
  PType type = pref_type_parse((char*)token->data.scalar.value);
  if (type != P_NONE) {
    yaml_parser_scan(parser, token);
    Value * val = NULL;
    if (token->type == YAML_VALUE_TOKEN)
    {
      yaml_parser_scan(parser, token);
      if (token->data.scalar.value){
        val = parse_value((char*)token->data.scalar.value);
      } else {
        val = parse_category(parser, token);
      }
    }else {
      return NULL;
    }
    if (val) {

      Preference * pref = preference_new(type, val);
      list = pref_list_add(list, pref);
    }
    return list;
  } else {
    printf("  >> Type P_NONE\n");
    return NULL;
  }
}


void
parse_element(Style         *style,
              yaml_parser_t *parser,
              yaml_token_t  *token)
{
  yaml_parser_scan(parser, token);
  if (token->type != YAML_SCALAR_TOKEN)
  {
    printf(">> Something wrong\n");
    return;
  }
  EType type = elem_type_parse((char*)token->data.scalar.value);
  if (type != E_NONE)
  {
    yaml_parser_scan(parser, token);

    Element * el = element_new(type);
    do{
      switch (token->type)
      {
      case YAML_KEY_TOKEN:
        el->list = parse_preference(el->list, parser, token);
        break;
      default:
        break;
      }
      yaml_parser_scan(parser, token);
    } while (token->type != YAML_BLOCK_END_TOKEN);
    style->list = elem_list_add(style->list, el);
  }else {
    printf(">> Type E_NONE\n");
  }
  return;
}

Style*
parse (char      *input)
{
  Style * style = style_new();
  yaml_parser_t parser;

  yaml_token_t  token;
  yaml_parser_initialize(&parser);

  size_t length = strlen(input);

  yaml_parser_set_input_string(&parser, (const unsigned char*)input, length);

  do {
    yaml_parser_scan(&parser, &token);
      switch(token.type)
      {
        /* Token types (read before actual token) */
      case YAML_KEY_TOKEN:
        parse_element(style, &parser, &token);
        break;
      default:
        break;
      }
    if(token.type != YAML_STREAM_END_TOKEN)
      yaml_token_delete(&token);
  } while(token.type != YAML_STREAM_END_TOKEN);
  /* Destroy the Parser object. */
  yaml_parser_delete(&parser);
  return style;
}
