#include "patternparser.h"

PatternParser::PatternParser(QObject *parent) : QObject(parent)
{
    left_delimeter = "{";
    right_delimeter = "}";
}

void PatternParser::setText(QString text)
{
    this->text = text;
}

QList<QString> PatternParser::getVariables()
{
    int start_position = 0;
    int pattern_begin = 0;
    int pattern_end = 0;
    QList<QString> result;
    pattern_begin = text.indexOf(left_delimeter, start_position);
    while (pattern_begin != -1) {
        pattern_end = text.indexOf(right_delimeter, pattern_begin + 1);
        if (pattern_end == -1) {
            break;
            //throw("Wrong pattern");
        }
        QString variable = text.mid(
            pattern_begin + left_delimeter.length(),
            pattern_end - pattern_begin - left_delimeter.length()
          );
        if (!result.contains(variable)) {
            result.append(
               variable
            );
        }
        //TODO: лучше бы end но пока убрал исключение
        start_position = pattern_end;
        pattern_begin = text.indexOf(left_delimeter, start_position);
    }
    return result;
}

QString PatternParser::parseTemplate(QMap<QString,QString> variable_map)
{
    QString replaced = text;
    QMap<QString, QString>::iterator i;
    for (i = variable_map.begin(); i != variable_map.end(); ++i) {
        QString for_replace = "";
        for_replace.append(left_delimeter).append(i.key()).append(right_delimeter);
        replaced = replaced.replace(for_replace, i.value());
    }
    return replaced;
}
