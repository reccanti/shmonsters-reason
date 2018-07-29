/**
 * A monster is a list of fields, and fields
 * have many types. The first element in a field
 * is the name of the field, while the second is
 * the value of the field
 */
type field =
  | Text(string, string)
  | LongText(string, string)
  | Image(string, string);

/**
 * Represents our generic monster. Contents
 * are retrieved via getter functions
 */
type t;

/**
 * Creates a monster from a list of fields
 */
let create: list(field) => t;

/**
 * Retrieve a field from the monster using its name
 */
let getField: (string, t) => option(field);

/**
 * Returns all of the monster's fields
 */
let getAllFields: t => list(field);