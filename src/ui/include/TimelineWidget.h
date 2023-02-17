//
// Created by xuyou on 23-2-17.
//

#ifndef KLOGG_TIMELINEWIDGET_H
#define KLOGG_TIMELINEWIDGET_H

#include "abstractlogview.h"
#include "linetypes.h"
#include <QListWidget>
#include <QMenu>
#include <QAction>

class TimelineWidget : public QListWidget {
    Q_OBJECT
  public:
    TimelineWidget(AbstractLogView* mainLogView, AbstractLogView* filteredLogView, QWidget* parent = nullptr);
    void addLinesToTimeline( const std::vector<LineNumber>& lines );
    void addToTimeline(uint64_t lineNumber, QString line, QString comment);

  private:
    void initPopMenu();

  private Q_SLOTS:
    void onItemDoubleClicked(QListWidgetItem *item);
    void onCustomContextMenuRequested(const QPoint &pos);
    void onDelete();
    void onClearAll();

  private:
    AbstractLogView* mainLogView_;
    AbstractLogView* filteredLogView_;

    QMenu* popMenu_;
    QAction* deleteAction_;
    QAction* cleanAction_;
};

#endif // KLOGG_TIMELINEWIDGET_H
