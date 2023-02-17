//
// Created by xuyou on 23-2-17.
//

#include "TimelineWidget.h"
#include "TimelineNode.h"
TimelineWidget::TimelineWidget( AbstractLogView* mainLogView, AbstractLogView* filteredLogView, QWidget* parent )
    : QListWidget( parent )
{
    mainLogView_ = mainLogView;
    filteredLogView_ = filteredLogView;
    setSpacing(10);
    connect(this, &QListWidget::itemDoubleClicked, this, &TimelineWidget::onItemDoubleClicked);
}

void TimelineWidget::addLinesToTimeline( const std::vector<LineNumber>& lines ) {
    for (auto line : lines) {
        addToTimeline(line.get(), mainLogView_->getLineString(line), QString(""));
    }
}

void TimelineWidget::addToTimeline( uint64_t lineNumber, QString detail, QString comment ) {
    const int listSize = this->count();
    // printf("TimelineWidget::addToTimeline %ld, list size = %d\n", lineNumber, listSize);
    auto timelineNode = new TimelineNode(lineNumber, detail, comment, this);
    auto listItem = new QListWidgetItem();
    listItem->setSizeHint(QSize(200,120));

    int pos = listSize;
    for (int row = 0; row < listSize; ++row ) {
        TimelineNode* tmpNode = dynamic_cast<TimelineNode*>( itemWidget( this->item( row ) ) );
        // printf("process %ld < %ld ?\n", lineNumber, tmpNode->getLineNumber());
        if(lineNumber < tmpNode->getLineNumber()) {
            pos = row;
            break;
        } else if (lineNumber == tmpNode->getLineNumber()) {
            return ;
        }
    }

    // printf("insert pos = %d\n", pos);
    insertItem(pos, listItem);
    setItemWidget( listItem, timelineNode );
}

void TimelineWidget::onItemDoubleClicked( QListWidgetItem* item ) {
    TimelineNode* node = dynamic_cast<TimelineNode*>( itemWidget( item ) );
    LineNumber line(node->getLineNumber());
    mainLogView_->trySelectLine(line);
    filteredLogView_->trySelectLine(filteredLogView_->lineIndex(line));
}

