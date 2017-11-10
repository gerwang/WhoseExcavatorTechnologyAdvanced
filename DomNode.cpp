//
// Created by Gerwa on 2017/11/7.
//

#include "DomNode.h"
#include "Logger.h"

const Pair<String, int> EscapeCharacters[] = {
        makePair("amp", 0x26),
        makePair("lt", 0x3c),
        makePair("gt", 0x3e),
        makePair("Agrave", 0xc0),
        makePair("Aacute", 0xc1),
        makePair("Acirc", 0xc2),
        makePair("Atilde", 0xc3),
        makePair("Auml", 0xc4),
        makePair("Aring", 0xc5),
        makePair("AElig", 0xc6),
        makePair("Ccedil", 0xc7),
        makePair("Egrave", 0xc8),
        makePair("Eacute", 0xc9),
        makePair("Ecirc", 0xca),
        makePair("Euml", 0xcb),
        makePair("Igrave", 0xcc),
        makePair("Iacute", 0xcd),
        makePair("Icirc", 0xce),
        makePair("Iuml", 0xcf),
        makePair("ETH", 0xd0),
        makePair("Ntilde", 0xd1),
        makePair("Ograve", 0xd2),
        makePair("Oacute", 0xd3),
        makePair("Ocirc", 0xd4),
        makePair("Otilde", 0xd5),
        makePair("Ouml", 0xd6),
        makePair("Oslash", 0xd8),
        makePair("Ugrave", 0xd9),
        makePair("Uacute", 0xda),
        makePair("Ucirc", 0xdb),
        makePair("Uuml", 0xdc),
        makePair("Yacute", 0xdd),
        makePair("THORN", 0xde),
        makePair("szlig", 0xdf),
        makePair("agrave", 0xe0),
        makePair("aacute", 0xe1),
        makePair("acirc", 0xe2),
        makePair("atilde", 0xe3),
        makePair("auml", 0xe4),
        makePair("aring", 0xe5),
        makePair("aelig", 0xe6),
        makePair("ccedil", 0xe7),
        makePair("egrave", 0xe8),
        makePair("eacute", 0xe9),
        makePair("ecirc", 0xea),
        makePair("euml", 0xeb),
        makePair("igrave", 0xec),
        makePair("iacute", 0xed),
        makePair("icirc", 0xee),
        makePair("iuml", 0xef),
        makePair("eth", 0xf0),
        makePair("ntilde", 0xf1),
        makePair("ograve", 0xf2),
        makePair("oacute", 0xf3),
        makePair("ocirc", 0xf4),
        makePair("otilde", 0xf5),
        makePair("ouml", 0xf6),
        makePair("oslash", 0xf8),
        makePair("ugrave", 0xf9),
        makePair("uacute", 0xfa),
        makePair("ucirc", 0xfb),
        makePair("uuml", 0xfc),
        makePair("yacute", 0xfd),
        makePair("thorn", 0xfe),
        makePair("yuml", 0xff),
        makePair("nbsp", 0xa0),
        makePair("iexcl", 0xa1),
        makePair("cent", 0xa2),
        makePair("pound", 0xa3),
        makePair("curren", 0xa4),
        makePair("yen", 0xa5),
        makePair("brvbar", 0xa6),
        makePair("sect", 0xa7),
        makePair("uml", 0xa8),
        makePair("copy", 0xa9),
        makePair("ordf", 0xaa),
        makePair("laquo", 0xab),
        makePair("not", 0xac),
        makePair("shy", 0xad),
        makePair("reg", 0xae),
        makePair("macr", 0xaf),
        makePair("deg", 0xb0),
        makePair("plusmn", 0xb1),
        makePair("sup2", 0xb2),
        makePair("sup3", 0xb3),
        makePair("acute", 0xb4),
        makePair("micro", 0xb5),
        makePair("para", 0xb6),
        makePair("cedil", 0xb8),
        makePair("sup1", 0xb9),
        makePair("ordm", 0xba),
        makePair("raquo", 0xbb),
        makePair("frac14", 0xbc),
        makePair("frac12", 0xbd),
        makePair("frac34", 0xbe),
        makePair("iquest", 0xbf),
        makePair("times", 0xd7),
        makePair("divide", 0xf7),
        makePair("forall", 0x2200),
        makePair("part", 0x2202),
        makePair("exist", 0x2203),
        makePair("empty", 0x2205),
        makePair("nabla", 0x2207),
        makePair("isin", 0x2208),
        makePair("notin", 0x2209),
        makePair("ni", 0x220b),
        makePair("prod", 0x220f),
        makePair("sum", 0x2211),
        makePair("minus", 0x2212),
        makePair("lowast", 0x2217),
        makePair("radic", 0x221a),
        makePair("prop", 0x221d),
        makePair("infin", 0x221e),
        makePair("ang", 0x2220),
        makePair("and", 0x2227),
        makePair("or", 0x2228),
        makePair("cap", 0x2229),
        makePair("cup", 0x222a),
        makePair("int", 0x222b),
        makePair("there4", 0x2234),
        makePair("sim", 0x223c),
        makePair("cong", 0x2245),
        makePair("asymp", 0x2248),
        makePair("ne", 0x2260),
        makePair("equiv", 0x2261),
        makePair("le", 0x2264),
        makePair("ge", 0x2265),
        makePair("sub", 0x2282),
        makePair("sup", 0x2283),
        makePair("nsub", 0x2284),
        makePair("sube", 0x2286),
        makePair("supe", 0x2287),
        makePair("oplus", 0x2295),
        makePair("otimes", 0x2297),
        makePair("perp", 0x22a5),
        makePair("sdot", 0x22c5),
        makePair("Alpha", 0x391),
        makePair("Beta", 0x392),
        makePair("Gamma", 0x393),
        makePair("Delta", 0x394),
        makePair("Epsilon", 0x395),
        makePair("Zeta", 0x396),
        makePair("Eta", 0x397),
        makePair("Theta", 0x398),
        makePair("Iota", 0x399),
        makePair("Kappa", 0x39a),
        makePair("Lambda", 0x39b),
        makePair("Mu", 0x39c),
        makePair("Nu", 0x39d),
        makePair("Xi", 0x39e),
        makePair("Omicron", 0x39f),
        makePair("Pi", 0x3a0),
        makePair("Rho", 0x3a1),
        makePair("Sigma", 0x3a3),
        makePair("Tau", 0x3a4),
        makePair("Upsilon", 0x3a5),
        makePair("Phi", 0x3a6),
        makePair("Chi", 0x3a7),
        makePair("Psi", 0x3a8),
        makePair("Omega", 0x3a9),
        makePair("alpha", 0x3b1),
        makePair("beta", 0x3b2),
        makePair("gamma", 0x3b3),
        makePair("delta", 0x3b4),
        makePair("epsilon", 0x3b5),
        makePair("zeta", 0x3b6),
        makePair("eta", 0x3b7),
        makePair("theta", 0x3b8),
        makePair("iota", 0x3b9),
        makePair("kappa", 0x3ba),
        makePair("lambda", 0x3bb),
        makePair("mu", 0x3bc),
        makePair("nu", 0x3bd),
        makePair("xi", 0x3be),
        makePair("omicron", 0x3bf),
        makePair("pi", 0x3c0),
        makePair("rho", 0x3c1),
        makePair("sigmaf", 0x3c2),
        makePair("sigma", 0x3c3),
        makePair("tau", 0x3c4),
        makePair("upsilon", 0x3c5),
        makePair("phi", 0x3c6),
        makePair("chi", 0x3c7),
        makePair("psi", 0x3c8),
        makePair("omega", 0x3c9),
        makePair("thetasym", 0x3d1),
        makePair("upsih", 0x3d2),
        makePair("piv", 0x3d6),
        makePair("OElig", 0x152),
        makePair("oelig", 0x153),
        makePair("Scaron", 0x160),
        makePair("scaron", 0x161),
        makePair("Yuml", 0x178),
        makePair("fnof", 0x192),
        makePair("circ", 0x2c6),
        makePair("tilde", 0x2dc),
        makePair("ensp", 0x2002),
        makePair("emsp", 0x2003),
        makePair("thinsp", 0x2009),
        makePair("zwnj", 0x200c),
        makePair("zwj", 0x200d),
        makePair("lrm", 0x200e),
        makePair("rlm", 0x200f),
        makePair("ndash", 0x2013),
        makePair("mdash", 0x2014),
        makePair("lsquo", 0x2018),
        makePair("rsquo", 0x2019),
        makePair("sbquo", 0x201a),
        makePair("ldquo", 0x201c),
        makePair("rdquo", 0x201d),
        makePair("bdquo", 0x201e),
        makePair("dagger", 0x2020),
        makePair("Dagger", 0x2021),
        makePair("bull", 0x2022),
        makePair("hellip", 0x2026),
        makePair("permil", 0x2030),
        makePair("prime", 0x2032),
        makePair("Prime", 0x2033),
        makePair("lsaquo", 0x2039),
        makePair("rsaquo", 0x203a),
        makePair("oline", 0x203e),
        makePair("euro", 0x20ac),
        makePair("trade", 0x2122),
        makePair("larr", 0x2190),
        makePair("uarr", 0x2191),
        makePair("rarr", 0x2192),
        makePair("darr", 0x2193),
        makePair("harr", 0x2194),
        makePair("crarr", 0x21b5),
        makePair("lceil", 0x2308),
        makePair("rceil", 0x2309),
        makePair("lfloor", 0x230a),
        makePair("rfloor", 0x230b),
        makePair("loz", 0x25ca),
        makePair("spades", 0x2660),
        makePair("clubs", 0x2663),
        makePair("hearts", 0x2665),
        makePair("diams", 0x2666),
        makePair("middot", 0xb7),
        makePair("quot", 0x22)
};

const LinkedList<Pair<String, int>> HtmlEscapeList(EscapeCharacters, EscapeCharacters + 240);

const String SelfClosingTags[] = {
        "!DOCTYPE",
        "area",
        "base",
        "br",
        "col",
        "embed",
        "hr",
        "img",
        "input",
        "keygen",
        "link",
        "menuitem",
        "meta",
        "param",
        "source",
        "track",
        "wbr"
};

const LinkedList<String> SelfClosingList(SelfClosingTags, SelfClosingTags + 17);

void DomNode::appendChild(DomNode *child) {
    m_children.push_back(child);
}

int DomNode::getEscapeCode(const String &str) {
    for (auto it = HtmlEscapeList.begin(); it != HtmlEscapeList.end(); ++it) {
        if (it->first == str) {
            return it->second;
        }
    }
    return -1;
}

bool DomNode::isSelfClosed(const String &tagName) {
    for (auto it = SelfClosingList.begin(); it != SelfClosingList.end(); ++it) {
        if (*it == tagName) {
            return true;
        }
    }
    return false;
}

bool DomNode::isNoEscape(const String &tagName) {
    return tagName == "style" || tagName == "script";
}

DomNode::~DomNode() {
    for (auto &child:m_children) {
        delete child;
        child = nullptr;
    }
}

/*!
 * for debug, slow implementation
 * @return the unescaped html
 */
String DomNode::innerHTML() {
//    if (m_nodeName.length() > 2000) {
//        Logger::slog("to long nodeName: " + m_nodeName);
//    }
    if (m_nodeType == Text) {
        return m_nodeName;
    } else if (m_nodeType == Comment) {
        return "<!--" + m_nodeName + "-->";
    } else if (m_nodeType == Document) {
        String res;
        for (auto &child:m_children) {
            res += child->innerHTML();
        }
        return res;
    } else if (m_nodeType == Element) {
        String res;
        res += "<";
        res += m_nodeName;
        if (m_className.length() > 0) {
            res += " class=\"" + m_className + "\"";
        }
        for (auto &pair:m_attributes) {
            res += " " + pair.first;
            if (pair.second.length() > 0) {
                res += "=\"" + pair.second + "\"";
            }
        }
        if (DomNode::isSelfClosed(m_nodeName)) {
            res += "/>";
        } else {
            res += ">";
            for (auto &child:m_children) {
                res += child->innerHTML();
            }
            res += "</";
            res += m_nodeName;
            res += ">";
        }
        return res;
    }
}

DomNode *DomNode::firstChild() {
    return *m_children.begin();
}

void DomNode::retrieveText(String &text) {
    if (m_nodeType == Text) {
        text += m_nodeName;
        return;
    }
    for (const auto &child:m_children) {
        child->retrieveText(text);
    }
}

String DomNode::text() {
    String res;
    retrieveText(res);
    return res;
}
