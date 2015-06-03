
function main() {
	// We can make arcs and circles:
    var path = new CSG.Path2D([ [10,-30] ]);
    path = path.concat(CSG.Path2D.arc({
      center: [0,0,0],
      radius: 10,
      startangle: 0,
      endangle: 90,
      resolution: 16,
    }));
    path = path.appendPoint([-5, 10]);
    path = path.appendPoint([-5, -5]);
    return path.rectangularExtrude(2, 20);
}