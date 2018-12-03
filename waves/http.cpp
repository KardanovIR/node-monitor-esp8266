#include "http.h"

#include "constants.h"

String makeTag(String tag, String content, String attributes) {
    String result = HTTP_OPEN_TAG;
    result += tag + attributes;
    result += HTTP_CLOSE_TAG;
    result += content;
    result += HTTP_OPEN_TAG;
    result += HTTP_END_TAG;
    result += tag;
    result += HTTP_CLOSE_TAG;
    return result;
}

String makeHead(String title) {
  String result = makeTag(HTTP_TITLE_TAG, title);
  result += HTTP_UTF8;
  return makeTag(HTTP_HEAD_TAG, result);
}

String makePage(String title, String content) {
    String preambule = HTTP_DOCTYPE;
    String head = makeHead(title);
    String body = makeTag(HTTP_BODY_TAG, content);
    return preambule + makeTag(HTTP_TAG, head + body);
}