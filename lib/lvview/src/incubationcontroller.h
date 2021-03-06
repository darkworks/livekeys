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

#ifndef LVINCUBATIONCONTROLLER_H
#define LVINCUBATIONCONTROLLER_H

#include <QObject>
#include <QQmlIncubationController>

#include "live/lvviewglobal.h"

namespace lv{

class LV_VIEW_EXPORT IncubationController : public QObject, public QQmlIncubationController{

    Q_OBJECT

public:
    IncubationController(QObject* parent = 0);
    ~IncubationController();

protected:
    virtual void timerEvent(QTimerEvent*);
};

/** Implementation of QObject function */
inline void IncubationController::timerEvent(QTimerEvent *){
    incubateFor(14);
}

}// namespace

#endif // LVINCUBATIONCONTROLLER_H
