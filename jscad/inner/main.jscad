// Inner holder for Wifi Chip, Charger, and Battery
include("common.jscad");

// Pass true to render the Wifi Chip, Charger and battery holder
function inner_objects(render_helper) {
	var battery = helper_object(battery_dim, inner_radius/2 + margin);
	var vertical_slab = object(
		vertical_slab_dim, 
		battery.getBounds()[1].y
	);

	var charger = helper_object(charger_dim, vertical_slab.getBounds()[1].y);
	var wifi = helper_object(
		wifi_dim, 
		vertical_slab.getBounds()[1].y, 
		charger.getBounds()[1].z + 1);

	var charger_hole = object(
		charger_hole_dim, 
		charger.getBounds()[1].y,
		0);

	var base = base_plate(inner_radius);
	var helpers = [battery, charger, wifi];
	var objects = [
		difference(base, 
			charger_hole, 
			screw_hole(0),
			screw_hole(1)),
		vertical_slab		
	];

	if(render_helper) {
		return objects.concat(helpers);
	} else {
		return objects;
	}
}

function main() {
	return inner_objects(false);
}