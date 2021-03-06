/***************************************************************************
                         qgspointv2.h
                         --------------
    begin                : September 2014
    copyright            : (C) 2014 by Marco Hugentobler
    email                : marco at sourcepole dot ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSPOINTV2_H
#define QGSPOINTV2_H

#include "qgis_core.h"
#include "qgis.h"
#include "qgsabstractgeometry.h"
#include "qgsrectangle.h"

/***************************************************************************
 * This class is considered CRITICAL and any change MUST be accompanied with
 * full unit tests in testqgsgeometry.cpp.
 * See details in QEP #17
 ****************************************************************************/

/** \ingroup core
 * \brief Point geometry type, with support for z-dimension and m-values.
 * \since QGIS 3.0, (previously QgsPointv2 since QGIS 2.10)
 */
class CORE_EXPORT QgsPoint: public QgsAbstractGeometry
{
    Q_GADGET

    Q_PROPERTY( double x READ x WRITE setX )
    Q_PROPERTY( double y READ y WRITE setY )
    Q_PROPERTY( double z READ z WRITE setZ )
    Q_PROPERTY( double m READ m WRITE setM )

  public:

    /**
     * Construct a point with the provided initial coordinate values.
     *
     * If \a wkbType is set to `QgsWkbTypes::Point`, `QgsWkbTypes::PointZ`, `QgsWkbTypes::PointM` or `QgsWkbTypes::PointZM`
     * the type will be set accordingly. If it is left to the default `QgsWkbTypes::Unknown`, the type will be set
     * based on the following rules:
     * - If only x and y are specified, the type will be a 2D point.
     * - If any or both of the Z and M are specified, the appropriate type will be created.
     *
     * \code{.py}
     *   pt = QgsPoint(43.4, 5.3)
     *   pt.exportToWkt() # Point(43.4 5.3)
     *
     *   pt_z = QgsPoint(120, 343, 77)
     *   pt.exportToWkt() # PointZ(120 343 77)
     *
     *   pt_m = QgsPoint(33, 88, m=5)
     *   pt_m.m() # 5
     *   pt_m.wkbType() # QgsWkbTypes.PointM
     *
     *   pt = QgsPoint(30, 40, wkbType=QgsWkbTypes.PointZ)
     *   pt.z() # nan
     *   pt.wkbType() # QgsWkbTypes.PointZ
     * \endcode
     */
#ifndef SIP_RUN
    QgsPoint( double x = 0.0, double y = 0.0, double z = std::numeric_limits<double>::quiet_NaN(), double m = std::numeric_limits<double>::quiet_NaN(), QgsWkbTypes::Type wkbType = QgsWkbTypes::Unknown );
#else
    QgsPoint( double x = 0.0, double y = 0.0, SIP_PYOBJECT z = Py_None, SIP_PYOBJECT m = Py_None, QgsWkbTypes::Type wkbType = QgsWkbTypes::Unknown ) [( double x = 0.0, double y = 0.0, double z = 0.0, double m = 0.0, QgsWkbTypes::Type wkbType = QgsWkbTypes::Unknown )];
    % MethodCode
    double z;
    double m;

    if ( a2 == Py_None )
    {
      z = std::numeric_limits<double>::quiet_NaN();
    }
    else
    {
      z = PyFloat_AsDouble( a2 );
    }

    if ( a3 == Py_None )
    {
      m = std::numeric_limits<double>::quiet_NaN();
    }
    else
    {
      m = PyFloat_AsDouble( a3 );
    }

    sipCpp = new sipQgsPoint( a0, a1, z, m, a4 );
    % End
#endif

    /** Construct a QgsPoint from a QgsPointXY object
     */
    explicit QgsPoint( const QgsPointXY &p );

    /** Construct a QgsPoint from a QPointF
     */
    explicit QgsPoint( QPointF p );

    /**
     * Create a new point with the given wkbtype and values.
     *
     * \note Not available in Python bindings
     */
    explicit QgsPoint( QgsWkbTypes::Type wkbType, double x = 0.0, double y = 0.0, double z = std::numeric_limits<double>::quiet_NaN(), double m = std::numeric_limits<double>::quiet_NaN() ) SIP_SKIP;

    bool operator==( const QgsPoint &pt ) const;
    bool operator!=( const QgsPoint &pt ) const;

    /** Returns the point's x-coordinate.
     * \see setX()
     * \see rx()
     */
    double x() const { return mX; }

    /** Returns the point's y-coordinate.
     * \see setY()
     * \see ry()
     */
    double y() const { return mY; }

    /** Returns the point's z-coordinate.
     * \see setZ()
     * \see rz()
     */
    double z() const { return mZ; }

    /** Returns the point's m value.
     * \see setM()
     * \see rm()
     */
    double m() const { return mM; }

    /** Returns a reference to the x-coordinate of this point.
     * Using a reference makes it possible to directly manipulate x in place.
     * \see x()
     * \see setX()
     * \note not available in Python bindings
     */
    double &rx() SIP_SKIP { clearCache(); return mX; }

    /** Returns a reference to the y-coordinate of this point.
     * Using a reference makes it possible to directly manipulate y in place.
     * \see y()
     * \see setY()
     * \note not available in Python bindings
     */
    double &ry() SIP_SKIP { clearCache(); return mY; }

    /** Returns a reference to the z-coordinate of this point.
     * Using a reference makes it possible to directly manipulate z in place.
     * \see z()
     * \see setZ()
     * \note not available in Python bindings
     */
    double &rz() SIP_SKIP { clearCache(); return mZ; }

    /** Returns a reference to the m value of this point.
     * Using a reference makes it possible to directly manipulate m in place.
     * \see m()
     * \see setM()
     * \note not available in Python bindings
     */
    double &rm() SIP_SKIP { clearCache(); return mM; }

    /** Sets the point's x-coordinate.
     * \see x()
     * \see rx()
     */
    void setX( double x )
    {
      clearCache();
      mX = x;
    }

    /** Sets the point's y-coordinate.
     * \see y()
     * \see ry()
     */
    void setY( double y )
    {
      clearCache();
      mY = y;
    }

    /** Sets the point's z-coordinate.
     * \note calling this will have no effect if the point does not contain a z-dimension. Use addZValue() to
     * add a z value and force the point to have a z dimension.
     * \see z()
     * \see rz()
     */
    void setZ( double z )
    {
      if ( !is3D() )
        return;
      clearCache();
      mZ = z;
    }

    /** Sets the point's m-value.
     * \note calling this will have no effect if the point does not contain a m-dimension. Use addMValue() to
     * add a m value and force the point to have an m dimension.
     * \see m()
     * \see rm()
     */
    void setM( double m )
    {
      if ( !isMeasure() )
        return;
      clearCache();
      mM = m;
    }

    /** Returns the point as a QPointF.
     * \since QGIS 2.14
     */
    QPointF toQPointF() const;

    /**
     * Returns the distance between this point and a specified x, y coordinate. In certain
     * cases it may be more appropriate to call the faster distanceSquared() method, e.g.,
     * when comparing distances.
     * \since QGIS 3.0
     * \see distanceSquared()
    */
    double distance( double x, double y ) const;

    /**
     * Returns the 2D distance between this point and another point. In certain
     * cases it may be more appropriate to call the faster distanceSquared() method, e.g.,
     * when comparing distances.
     * \since QGIS 3.0
    */
    double distance( const QgsPoint &other ) const;

    /**
     * Returns the squared distance between this point a specified x, y coordinate. Calling
     * this is faster than calling distance(), and may be useful in use cases such as comparing
     * distances where the extra expense of calling distance() is not required.
     * \see distance()
     * \since QGIS 3.0
    */
    double distanceSquared( double x, double y ) const;

    /**
     * Returns the squared distance between this point another point. Calling
     * this is faster than calling distance(), and may be useful in use cases such as comparing
     * distances where the extra expense of calling distance() is not required.
     * \see distance()
     * \since QGIS 3.0
    */
    double distanceSquared( const QgsPoint &other ) const;

    /**
     * Returns the 3D distance between this point and a specified x, y, z coordinate. In certain
     * cases it may be more appropriate to call the faster distanceSquared() method, e.g.,
     * when comparing distances.
     * \since QGIS 3.0
     * \see distanceSquared()
    */
    double distance3D( double x, double y, double z ) const;

    /**
     * Returns the 3D distance between this point and another point. In certain
     * cases it may be more appropriate to call the faster distanceSquared() method, e.g.,
     * when comparing distances.
     * \since QGIS 3.0
    */
    double distance3D( const QgsPoint &other ) const;

    /**
     * Returns the 3D squared distance between this point a specified x, y, z coordinate. Calling
     * this is faster than calling distance(), and may be useful in use cases such as comparing
     * distances where the extra expense of calling distance() is not required.
     * \see distance()
     * \since QGIS 3.0
    */
    double distanceSquared3D( double x, double y, double z ) const;

    /**
     * Returns the 3D squared distance between this point another point. Calling
     * this is faster than calling distance(), and may be useful in use cases such as comparing
     * distances where the extra expense of calling distance() is not required.
     * \see distance()
     * \since QGIS 3.0
    */
    double distanceSquared3D( const QgsPoint &other ) const;

    /**
     * Calculates azimuth between this point and other one (clockwise in degree, starting from north)
     * \since QGIS 3.0
     */
    double azimuth( const QgsPoint &other ) const;

    /**
     * Calculates inclination between this point and other one (starting from zenith = 0 to nadir = 180. Horizon = 90)
     * Returns 90.0 if the distance between this point and other one is equal to 0 (same point).
     * \since QGIS 3.0
     */
    double inclination( const QgsPoint &other ) const;

    /** Returns a new point which correspond to this point projected by a specified distance
     * with specified angles (azimuth and inclination).
     * M value is preserved.
     * \param distance distance to project
     * \param azimuth angle to project in X Y, clockwise in degrees starting from north
     * \param inclination angle to project in Z (3D). If the point is 2D, the Z value is assumed to be 0.
     * \returns The point projected. If a 2D point is projected a 3D point will be returned except if
     *  inclination is 90. A 3D point is always returned if a 3D point is projected.
     * Example:
     * \code{.py}
     *   p = QgsPoint( 1, 2 ) # 2D point
     *   pr = p.project ( 1, 0 )
     *   # pr is a 2D point: 'Point (1 3)'
     *   pr = p.project ( 1, 0, 90 )
     *   # pr is a 2D point: 'Point (1 3)'
     *   pr = p.project (1, 0, 0 )
     *   # pr is a 3D point: 'PointZ (1 2 1)'
     *   p = QgsPoint( QgsWkbTypes.PointZ, 1, 2, 2 ) # 3D point
     *   pr = p.project ( 1, 0 )
     *   # pr is a 3D point: 'PointZ (1 3 2)'
     *   pr = p.project ( 1, 0, 90 )
     *   # pr is a 3D point: 'PointZ (1 3 2)'
     *   pr = p.project (1, 0, 0 )
     *   # pr is a 3D point: 'PointZ (1 2 3)'
     * \endcode
     * \since QGIS 3.0
     */
    QgsPoint project( double distance, double azimuth, double inclination = 90.0 ) const;

    /**
     * Calculates the vector obtained by subtracting a point from this point.
     * \since QGIS 3.0
     */
    QgsVector operator-( const QgsPoint &p ) const { return QgsVector( mX - p.mX, mY - p.mY ); }

    /**
     * Adds a vector to this point in place.
     * \since QGIS 3.0
     */
    QgsPoint &operator+=( QgsVector v ) { mX += v.x(); mY += v.y(); return *this; }

    /**
     * Subtracts a vector from this point in place.
     * \since QGIS 3.0
     */
    QgsPoint &operator-=( QgsVector v ) { mX -= v.x(); mY -= v.y(); return *this; }

    /**
     * Adds a vector to this point.
     * \since QGIS 3.0
     */
    QgsPoint operator+( QgsVector v ) const { QgsPoint r = *this; r.rx() += v.x(); r.ry() += v.y(); return r; }

    /**
     * Subtracts a vector from this point.
     * \since QGIS 3.0
     */
    QgsPoint operator-( QgsVector v ) const { QgsPoint r = *this; r.rx() -= v.x(); r.ry() -= v.y(); return r; }

    //implementation of inherited methods
    bool isEmpty() const override { return false; }
    virtual QgsRectangle boundingBox() const override { return QgsRectangle( mX, mY, mX, mY ); }
    virtual QString geometryType() const override { return QStringLiteral( "Point" ); }
    virtual int dimension() const override { return 0; }
    virtual QgsPoint *clone() const override SIP_FACTORY;
    void clear() override;
    virtual bool fromWkb( QgsConstWkbPtr &wkb ) override;
    virtual bool fromWkt( const QString &wkt ) override;
    QByteArray asWkb() const override;
    QString asWkt( int precision = 17 ) const override;
    QDomElement asGML2( QDomDocument &doc, int precision = 17, const QString &ns = "gml" ) const override;
    QDomElement asGML3( QDomDocument &doc, int precision = 17, const QString &ns = "gml" ) const override;
    QString asJSON( int precision = 17 ) const override;
    void draw( QPainter &p ) const override;
    void transform( const QgsCoordinateTransform &ct, QgsCoordinateTransform::TransformDirection d = QgsCoordinateTransform::ForwardTransform,
                    bool transformZ = false ) override;
    void transform( const QTransform &t ) override;
    virtual QgsCoordinateSequence coordinateSequence() const override;
    virtual int nCoordinates() const override { return 1; }
    virtual QgsAbstractGeometry *boundary() const override SIP_FACTORY;

    //low-level editing
    virtual bool insertVertex( QgsVertexId position, const QgsPoint &vertex ) override { Q_UNUSED( position ); Q_UNUSED( vertex ); return false; }
    virtual bool moveVertex( QgsVertexId position, const QgsPoint &newPos ) override;
    virtual bool deleteVertex( QgsVertexId position ) override { Q_UNUSED( position ); return false; }

    virtual double closestSegment( const QgsPoint &pt, QgsPoint &segmentPt SIP_OUT,
                                   QgsVertexId &vertexAfter SIP_OUT, bool *leftOf SIP_OUT,
                                   double epsilon ) const override;
    bool nextVertex( QgsVertexId &id, QgsPoint &vertex SIP_OUT ) const override;

    /** Angle undefined. Always returns 0.0
        \param vertex the vertex id
        \returns 0.0*/
    double vertexAngle( QgsVertexId vertex ) const override { Q_UNUSED( vertex ); return 0.0; }

    virtual int vertexCount( int /*part*/ = 0, int /*ring*/ = 0 ) const override { return 1; }
    virtual int ringCount( int /*part*/ = 0 ) const override { return 1; }
    virtual int partCount() const override { return 1; }
    virtual QgsPoint vertexAt( QgsVertexId /*id*/ ) const override { return *this; }

    virtual bool addZValue( double zValue = 0 ) override;
    virtual bool addMValue( double mValue = 0 ) override;
    virtual bool dropZValue() override;
    virtual bool dropMValue() override;
    bool convertTo( QgsWkbTypes::Type type ) override;

#ifndef SIP_RUN

    /**
     * Cast the \a geom to a QgsPoint.
     * Should be used by qgsgeometry_cast<QgsPoint *>( geometry ).
     *
     * \note Not available in Python. Objects will be automatically be converted to the appropriate target type.
     * \since QGIS 3.0
     */
    inline const QgsPoint *cast( const QgsAbstractGeometry *geom ) const
    {
      if ( geom && QgsWkbTypes::flatType( geom->wkbType() ) == QgsWkbTypes::Point )
        return static_cast<const QgsPoint *>( geom );
      return nullptr;
    }
#endif
  private:
    double mX;
    double mY;
    double mZ;
    double mM;
};

#endif // QGSPOINTV2_H
