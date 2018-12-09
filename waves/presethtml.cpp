#include "presethtml.h"

#include "constants.h"
#include "http.h"

String makeWavesLogo()
{
    return makeTag(HTTP_P_TAG, makeTag(HTTP_B_TAG, "waves") + makeTag(HTTP_SUP_TAG, "", "style='width:10px;height:10px;background:#0056FF;transform:rotate(45deg);display:inline-block;margin-left:3px;'"), "style='font-size:40px'");
}

String makeWavesLabel()
{
    return makeTag(HTTP_P_TAG, CONTENT_LABEL, "style='font-size:12px;'");
}

String makeBR()
{
    return HTTP_OPEN_TAG + String("br") + HTTP_END_TAG + HTTP_CLOSE_TAG;
}

String makeTableRow2(String label, String value, String id)
{
    return makeTag(HTTP_TR_TAG, makeTag(HTTP_TH_TAG, label, "class='right'") + makeTag(HTTP_TH_TAG, value, (id.length() ? "id='" + id + "' " : "") + " class='left'"));
}

String makeAjax(byte timeout)
{
    String timeoutString((timeout > 0 ? timeout : 1) * 1000);
    return String("function ajax(){var e=new XMLHttpRequest;e.onreadystatechange=function(){if(4==this.readyState&&200==this.status){var e=JSON.parse(this.responseText);for(var t in e)document.getElementById(t).innerHTML=e[t]}},e.open('GET','/state',!0),e.send()}setInterval(ajax," + timeoutString + ");");
}