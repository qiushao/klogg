//
// Created by xuyou on 23-2-17.
//

#ifndef KLOGG_TIMELINENODE_H
#define KLOGG_TIMELINENODE_H

#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

class TimelineNode : public QWidget {
    Q_OBJECT
  public:
    TimelineNode(uint64_t lineNumber, QString text, QString comment, QWidget* parent = nullptr);

    uint64_t getLineNumber();

  private:
    uint64_t lineNumber_;
    QString text_;
    QString comment_;

    QLabel *lineNumberLabel_;
    QLabel *textLabel_;
    QLineEdit *commentEdit_;
    QHBoxLayout *lineInfoLayout_;
    QVBoxLayout *mainLayout_;
};

#endif // KLOGG_TIMELINENODE_H
