/****************************************************************************
**
** Copyright (C) 2014-2019 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of Livekeys Application.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
****************************************************************************/

#ifndef LVQMLSCRIPT_H
#define LVQMLSCRIPT_H

#include <QObject>
#include <QStringList>

namespace lv{

class Environment;
class Runnable;

class QmlScript : public QObject{

    Q_OBJECT
    Q_PROPERTY(QStringList  argv             READ argv        NOTIFY argvChanged)
    Q_PROPERTY(QStringList  argvTail         READ argvTail    CONSTANT)
    Q_PROPERTY(lv::Environment* environment READ environment CONSTANT)

public:
    QmlScript(const QStringList& argvTail, QObject* parent = 0);
    QmlScript(const std::vector<std::string>& argvTail, QObject* parent = 0);
    ~QmlScript();

    const QStringList& argv() const;
    const QStringList& argvTail() const;

    lv::Environment* environment();

public slots:
    void scriptChanged(lv::Runnable* active);
    const QString& name() const;

signals:
    void argvChanged();

private:
    QStringList       m_argvTail;
    QStringList       m_argv;
    lv::Environment* m_environment;

};

inline const QStringList &QmlScript::argv() const{
    return m_argv;
}

inline const QStringList &QmlScript::argvTail() const{
    return m_argvTail;
}

inline Environment *QmlScript::environment(){
    return m_environment;
}

inline const QString &QmlScript::name() const{
    return m_argv.first();
}

}// namespace

#endif // LVQMLSCRIPT_H
