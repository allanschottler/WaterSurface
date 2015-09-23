/* 
 * File:   WaterSurfaceNode.cpp
 * Author: allanws
 * 
 * Created on September 23, 2015, 2:52 PM
 */

#include <sys/param.h>

#include "WaterSurfaceNode.h"
#include "NoiseTexture3D.h"
#include "PolarGridGeometry.h"


WaterSurfaceNode::WaterSurfaceNode( unsigned int heightMapLevels, 
                                    unsigned int polarGridRadialSize, 
                                    unsigned int polarGridAngularSize ) 
{
    _heightMapLevels = heightMapLevels;
    
    _geode = new osg::Geode();    
    _geode->addDrawable( osg::ref_ptr< PolarGridGeometry >( new PolarGridGeometry( polarGridRadialSize, polarGridAngularSize ) ) );
        
    buildVertexTextures();
    
    _shader.linkStateSet( _geode->getOrCreateStateSet() );
}


WaterSurfaceNode::~WaterSurfaceNode() 
{
}


void WaterSurfaceNode::buildVertexTextures()
{
    for( unsigned int iLevel = 0; iLevel < _heightMapLevels; iLevel++ )
    {
        _geode->getOrCreateStateSet()->setTextureAttributeAndModes( iLevel, new NoiseTexture3D( powerof2( iLevel ) ), osg::StateAttribute::ON );
    }
}