//
// Copyright (c) 2009-2014 Shawn Singh, Glen Berseth, Mubbasir Kapadia, Petros Faloutsos, Glenn Reinman
// See license.txt for complete license.
//

#ifndef __STEERLIB_BOX_OBSTACLE_H__
#define __STEERLIB_BOX_OBSTACLE_H__

/// @file BoxObstacle.h
/// @brief Declares the BoxObstacle class
/// @todo
///   - remove the hard-coded arbitrary value for getTraversalCost


#include "interfaces/ObstacleInterface.h"
#include "Globals.h"


namespace SteerLib {


	class STEERLIB_API BoxObstacle : public SteerLib::ObstacleInterface
	{
	public:
		BoxObstacle(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax, float traversalCost=1001.0f) : _bounds(xmin, xmax, ymin, ymax, zmin, zmax), _traversalCost(traversalCost) { _blocksLineOfSight = (ymax > 0.7) ? true : false; }
		BoxObstacle(const Util::AxisAlignedBox & newBounds, float traversalCost=1001.0f ) : _bounds(newBounds), _traversalCost(traversalCost) { _blocksLineOfSight = (newBounds.ymax > 0.7) ? true : false; }

		// ObstacleInterface functionality (not all virtual functions were overridden here)
		void draw(); // implementation in .cpp
		const Util::AxisAlignedBox & getBounds() { return _bounds; }

        virtual void returnVertices(std::vector<Util::Vector>& _out) {
		_out.push_back(Util::Vector(_bounds.xmin, 0, _bounds.zmin));
		_out.push_back(Util::Vector(_bounds.xmin, 0, _bounds.zmax));
		_out.push_back(Util::Vector(_bounds.xmax, 0, _bounds.zmax));
		_out.push_back(Util::Vector(_bounds.xmax, 0, _bounds.zmin));
	}

		/// @name The SpatialDatabaseItem interface
		/// @brief The BoxObstacle implementation of this interface represents a box that blocks line of sight if it is taller than 0.5 meter, and cannot be traversed.
		//@{
		virtual bool isAgent() { return false; }
		bool blocksLineOfSight() { return _blocksLineOfSight; }
		float getTraversalCost() { return _traversalCost; }
		virtual bool intersects(const Util::Ray &r, float &t) { return Util::rayIntersectsBox2D(_bounds.xmin, _bounds.xmax, _bounds.zmin, _bounds.zmax, r, t); }
		virtual bool overlaps(const Util::Point & p, float radius) { return Util::boxOverlapsCircle2D(_bounds.xmin, _bounds.xmax, _bounds.zmin, _bounds.zmax,p, radius); }
		virtual float computePenetration(const Util::Point & p, float radius) { return Util::computeBoxCirclePenetration2D(_bounds.xmin, _bounds.xmax, _bounds.zmin, _bounds.zmax, p, radius); }
		//@}

	protected:
		Util::AxisAlignedBox _bounds;
		bool _blocksLineOfSight;
		float _traversalCost;
	};

}
#endif

