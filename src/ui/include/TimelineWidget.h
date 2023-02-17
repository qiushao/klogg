//
// Created by xuyou on 23-2-17.
//

#ifndef KLOGG_TIMELINEWIDGET_H
#define KLOGG_TIMELINEWIDGET_H

#include <QListWidget>
#include "linetypes.h"

class TimelineWidget : public QListWidget {
    Q_OBJECT
  public:
    TimelineWidget(QWidget* parent = nullptr);
    void addToTimeline( const std::vector<LineNumber>& lines );

};

#endif // KLOGG_TIMELINEWIDGET_H
