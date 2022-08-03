import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from .. import CONFIG_SCHEMA, hs2xx3a_ns

HS2xx3ABinarySensor = hs2xx3a_ns.class_('HS2xx3ABinarySensor', binary_sensor.BinarySensor, cg.Component)

CONFIG_SCHEMA = CONFIG_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(HS2xx3ABinarySensor),
}).extend(cv.COMPONENT_SCHEMA)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield binary_sensor.register_binary_sensor(var, config)