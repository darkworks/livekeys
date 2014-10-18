/****************************************************************************
**
** Copyright (C) 2014 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of Live CV application.
**
** GNU General Public License Usage
** 
** This file may be used under the terms of the GNU General Public License 
** version 3.0 as published by the Free Software Foundation and appearing 
** in the file LICENSE.GPL included in the packaging of this file.  Please 
** review the following information to ensure the GNU General Public License 
** version 3.0 requirements will be met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/
#include "QHoughLinesP.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

using namespace cv;
using namespace std;

/*!
  \qmltype HoughLinesP
  \instantiates QHoughLinesP
  \inqmlmodule lcvimgproc
  \inherits MatFilter
  \brief

  \quotefile imgproc/.qml
*/

/*!
  \class QHoughLinesP
  \inmodule lcvimgproc_cpp
  \brief
 */


class QHoughLinesPPrivate{

public :
    vector<Vec4i> lines;
    bool          linesDirty;
    bool          outDirty;

};

/*!
  \brief QHoughLinesP constructor

  Parameters:
  \a parent
 */
QHoughLinesP::QHoughLinesP(QQuickItem *parent)
    : QMatFilter(parent)
    , m_rho(1)
    , m_theta(1)
    , m_threshold(1)
    , m_minLineLength(0)
    , m_maxLineGap(0)
    , m_lineColor(QColor(255, 255, 255))
    , m_lineThickness(1)
    , d_ptr(new QHoughLinesPPrivate){

    Q_D(QHoughLinesP);
    d->linesDirty = false;
    d->outDirty   = false;
}

/*!
  \brief QHoughLinesP destructor
 */
QHoughLinesP::~QHoughLinesP(){
    delete d_ptr;
}

/*!
  \brief Filtering function.

  Parameters:
  \a in
  \a out
 */
void QHoughLinesP::transform(cv::Mat &in, cv::Mat&){
    Q_D(QHoughLinesP);
    if ( in.size() != Size(0, 0) ){
        if ( m_rho > 0 && m_theta > 0 && m_threshold > 0 )
            HoughLinesP(in, d->lines, m_rho, m_theta, m_threshold, m_minLineLength, m_maxLineGap );
        else
            qDebug() << "OpenCV Error ( HoughLinesP ) : rho, theta and threshold must be positive";
    }
    d->linesDirty = true;
    d->outDirty   = true;
}

QSGNode *QHoughLinesP::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *nodeData){
    Q_D(QHoughLinesP);
    if ( d->outDirty ){
        Mat* surface = output()->cvMat();
        surface->create(inputMat()->cvMat()->size(), CV_8UC4);
        surface->setTo(Scalar(0, 0, 0, 0));
        for( size_t i = 0; i < d->lines.size(); ++i ){
            line( *surface, Point(d->lines[i][0], d->lines[i][1]),
                Point(d->lines[i][2], d->lines[i][3]), Scalar(m_lineColor.blue(), m_lineColor.green(), m_lineColor.red(), 255), m_lineThickness, 8 );
        }
        d->outDirty = false;
    }
    return QMatDisplay::updatePaintNode(node, nodeData);
}