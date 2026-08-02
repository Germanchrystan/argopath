type Color = {
  r: number;
  g: number;
  b: number;
  a: number;
};

export type FieldValue = string | number | boolean | Color;

export type EntityPrototypeField = {
  name: string;
  type: number;
  defaultValue: FieldValue;
};

export type Entity = {
  name: string;
  fields: EntityPrototypeField[];
  color: Color;
};