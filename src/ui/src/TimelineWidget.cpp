//
// Created by xuyou on 23-2-17.
//

#include "TimelineWidget.h"
#include "TimelineNodeWidget.h"
#include <QMessageBox>
TimelineWidget::TimelineWidget( AbstractLogView* mainLogView, AbstractLogView* filteredLogView, QWidget* parent )
    : QListWidget( parent )
{
    mainLogView_ = mainLogView;
    filteredLogView_ = filteredLogView;
    setSpacing(10);
    setProperty("contextMenuPolicy", Qt::CustomContextMenu);
    initPopMenu();
    connect(this, &QWidget::customContextMenuRequested, this, &TimelineWidget::onCustomContextMenuRequested);
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
    auto timelineNode = new TimelineNodeWidget(lineNumber, detail, comment, this);
    auto listItem = new QListWidgetItem();
    listItem->setSizeHint(QSize(200,120));

    int pos = listSize;
    for (int row = 0; row < listSize; ++row ) {
        TimelineNodeWidget* tmpNode = dynamic_cast<TimelineNodeWidget*>( itemWidget( this->item( row ) ) );
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
    TimelineNodeWidget* node = dynamic_cast<TimelineNodeWidget*>( itemWidget( item ) );
    LineNumber line(node->getLineNumber());
    auto filterLine = filteredLogView_->lineIndex(line);
    filteredLogView_->trySelectLine(filterLine);
    mainLogView_->trySelectLine(line);
}

void TimelineWidget::onCustomContextMenuRequested( const QPoint& pos ) {
    Q_UNUSED(pos);
    popMenu_->exec(QCursor::pos());
}

void TimelineWidget::initPopMenu() {
    popMenu_ = new QMenu(this);
    deleteAction_ = new QAction(tr("Delete"), this);
    cleanAction_ = new QAction(tr("ClearAll"), this);
    popMenu_->addAction(deleteAction_);
    popMenu_->addAction(cleanAction_);
    connect(deleteAction_, &QAction::triggered, this, &TimelineWidget::onDelete);
    connect(cleanAction_, &QAction::triggered, this, &TimelineWidget::onClearAll);
}

void TimelineWidget::onDelete() {
    QList<QListWidgetItem*> items = selectedItems();
    if (items.count() > 0)
    {
        if (QMessageBox::Yes == QMessageBox::question(this, QStringLiteral("Remove Item"), QStringLiteral("Remove %1 item")
                                                                                                   .arg(QString::number(items.count())), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
        {
            for (auto item : items){
                removeItemWidget( item );
                items.removeOne( item );
                delete item;
            }
        }
    }
}

void TimelineWidget::onClearAll() {
    if (QMessageBox::Yes == QMessageBox::question(this, QStringLiteral("Remove Item"), QStringLiteral("Remove all item"),
                                                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
    {
        auto listSize = this->count();
        for ( int i = 0; i < listSize; ++i ) {
            QListWidgetItem* item = this->takeItem(0);
            delete item;
        }
    }
}
