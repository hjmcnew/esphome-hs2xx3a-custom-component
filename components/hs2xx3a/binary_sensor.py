import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import CONF_ID

hs2xx3a_binary_sensor_ns = cg.esphome_ns.namespace('hs2xx3a_binary_sensor')

HS2xx3ABinarySensor = hs2xx3a_binary_sensor_ns.class_('HS2xx3ABinarySensor', binary_sensor.BinarySensor, cg.Component)

CONFIG_SCHEMA = binary_sensor.BINARY_SENSOR_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(HS2xx3ABinarySensor),
}).extend(cv.COMPONENT_SCHEMA)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield binary_sensor.register_binary_sensor(var, config)