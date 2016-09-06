#ifndef PATTERNPARSER_H
#define PATTERNPARSER_H

#include <QObject>
#include <iterator>
#include <QMap>

class PatternParser : public QObject
{
    Q_OBJECT
public:
    explicit PatternParser(QObject *parent = 0);
    void setText(QString text);
    QList<QString> getVariables();
    QString parseTemplate(QMap<QString,QString> map);
signals:

public slots:

private:
    QString text;
    QString left_delimeter;
    QString right_delimeter;
};

#endif // PATTERNPARSER_H
