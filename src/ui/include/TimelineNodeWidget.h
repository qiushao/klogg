//
// Created by xuyou on 23-2-17.
//

#ifndef KLOGG_TIMELINENODEWIDGET_H
#define KLOGG_TIMELINENODEWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "TimelineNodeInfo.h"

class TimelineNodeWidget : public QWidget {
    Q_OBJECT
  public:
    TimelineNodeWidget( TimelineNodeInfo nodeInfo, QWidget* parent = nullptr);
    TimelineNodeWidget(uint64_t lineNumber, QString text, QString comment, QWidget* parent = nullptr);

    uint64_t getLineNumber();
    const TimelineNodeInfo& getTimelineNodeInfo();

  private:
    TimelineNodeInfo nodeInfo_;

    QLabel *lineNumberLabel_;
    QLabel *textLabel_;
    QLineEdit *commentEdit_;
    QHBoxLayout *lineInfoLayout_;
    QVBoxLayout *mainLayout_;
};

#endif // KLOGG_TIMELINENODEWIDGET_H
