//
// Created by xuyou on 23-2-17.
//

#include "TimelineWidget.h"
TimelineWidget::TimelineWidget( QWidget* parent )
    : QListWidget( parent )
{
}

void TimelineWidget::addToTimeline( const std::vector<LineNumber>& lines ) {
    for (auto line : lines) {
        printf("TimelineWidget::addToTimeline %lu\n", line.get());
    }
}
