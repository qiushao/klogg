//
// Created by xuyou on 23-2-21.
//

#ifndef KLOGG_TIMELINENODEINFO_H
#define KLOGG_TIMELINENODEINFO_H

struct TimeLineNodeInfo {
    TimeLineNodeInfo() {}
    TimeLineNodeInfo(uint64_t line, QString str, QString cm)
    : lineNumber(line)
    , text(str)
    , comment(cm) {

    }

    uint64_t lineNumber;
    QString text;
    QString comment;
};

#endif // KLOGG_TIMELINENODEINFO_H
