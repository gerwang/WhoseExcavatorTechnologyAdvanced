//
// Created by Gerwa on 2017/11/9.
//

#include "Crawler.h"
#include "HttpRequest.h"
#include "HTMLParser.h"
#include "cQuery.h"
#include "Logger.h"

ArrayList<String> Crawler::crawl(const String &url) {
    HttpRequest request;
    String html = request.get(url);
    HTMLParser parser;
    DomNode *document = parser.parseHTML(html);
    ArrayList<String> result;
    ArrayList<DomNode *> div_pt_bm_cl;
    cQuery().tag("div").attr("id", "pt").clas("bm").clas("cl").select(document, div_pt_bm_cl);
    if (div_pt_bm_cl.empty()) {
        Logger::slog("cannot find id=\"pt\" at " + url);
        return result;
    }
    ArrayList<DomNode *> div_z;
    cQuery().tag("div").clas("z").select(div_pt_bm_cl.front(), div_z);
    if (div_z.empty()) {
        Logger::slog("cannot find class=\"z\" at " + url);
        return result;
    }
    ArrayList<DomNode *> all_a;
    cQuery().tag("a").select(div_z.front(), all_a);
    if (all_a.size() < 5) {
        Logger::slog("cannot find enough a at " + url);
        return result;
    }
    result.push_back(all_a[2]->text());//发帖大类
    result.push_back(all_a[3]->text());//发帖小类
    result.push_back(all_a[4]->text());//发帖标题

    ArrayList<DomNode *> td_t_f;
    cQuery().tag("td").clas("t_f").attr("id", "").select(document, td_t_f);
    if (td_t_f.empty()) {
        Logger::slog("cannot find t_f at " + url);
        return result;
    }
    result.push_back(td_t_f.front()->text());//发帖内容

    ArrayList<DomNode *> a_xw1;
    cQuery().tag("a").clas("xw1").attr("target", "_blank").select(document, a_xw1);
    if (a_xw1.empty()) {
        Logger::slog("cannot find a_xw1 at " + url);
        return result;
    }
    result.push_back(a_xw1.front()->text());//发帖人
    ArrayList<DomNode *> div_pti;
    cQuery().tag("div").clas("pti").select(document, div_pti);
    if (div_pti.empty()) {
        Logger::slog("cannot find div_pti at " + url);
        return result;
    }
    ArrayList<DomNode *> div_authi;
    cQuery().tag("div").clas("authi").select(div_pti.front(), div_authi);
    String date = div_authi.front()->firstChild()->text();
    int index = 0, end_index = date.length() - 1;
    while (index < end_index && date[index] != ' ') {
        index++;
    }
    index++;
    while (index < end_index && date[end_index] != ' ') {
        end_index--;
    }
    result.push_back(date.substr(static_cast<unsigned int>(index), static_cast<unsigned int>(end_index)));//发帖日期
    ArrayList<DomNode *> div_ts_z_h1;
    cQuery().tag("div").clas("ts").clas("z").clas("h1").select(document, div_ts_z_h1);
    if (div_ts_z_h1.empty()) {
        Logger::slog("cannot find div_ts_z_h1 at " + url);
        return result;
    }
    String topic = div_ts_z_h1.front()->firstChild()->text();
    result.push_back(topic.substr(1, topic.length() - 1));//发帖类型
    delete document;
    return result;
}
