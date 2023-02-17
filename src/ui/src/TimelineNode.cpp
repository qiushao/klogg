//
// Created by xuyou on 23-2-17.
//

#include "TimelineNode.h"
TimelineNode::TimelineNode( uint64_t lineNumber, QString text, QString comment, QWidget* parent): QWidget(parent) {
    lineNumber_ = lineNumber;
    text_ = text;
    comment_ = comment;

    lineNumberLabel_ = new QLabel(QString::number(lineNumber + 1), this);
    lineNumberLabel_->setMaximumWidth(65);
    textLabel_ = new QLabel(text, this);
    textLabel_->setWordWrap(true);
    commentEdit_ = new QLineEdit(comment, this);
    lineInfoLayout_ = new QHBoxLayout();
    mainLayout_ = new QVBoxLayout();
    lineInfoLayout_->addWidget(lineNumberLabel_);
    lineInfoLayout_->addSpacing(10);
    lineInfoLayout_->addWidget(textLabel_);
    mainLayout_->addLayout(lineInfoLayout_);
    mainLayout_->addWidget(commentEdit_);
    setLayout(mainLayout_);
}

uint64_t TimelineNode::getLineNumber()
{
    return lineNumber_;
}
