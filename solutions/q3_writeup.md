# Question 3: Determine if a path intersects with an obstacle

I would write a function that does the following:

1. ### In the XY plane, look for where the path and obstacle projects intersection

   I would do this by first converting the circle from a polar coordinate equasion to cartesian
   and seeing where it intersects with each edge of the polygon. I would then convert these points
   back to polar coordinates and add them to a set including the start and end angle.

2. ### Determine whether the midpoint between any 2 adjacent points in this set lies inside the convex polygon in the XY plane

   I would do this by taking the cross product of the point in question with every edge of the
   polygon. If the cross product is +, then I know that the point is to the right of the edge.
   If I do this for every edge, then I know the point is to the right of every edge, and therefore
   I can conclude the point is in the XY projection of the polygon

3. ### Determine if the height of the path pieces in the polygon (in XY space) overlap with any part of the polygons height

   I would do this by just taking the minimum height between any of edge points we determined were
   inside and checking if its <= the obstacle height
