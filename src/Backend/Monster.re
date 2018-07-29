/**
 * A monster is a list of fields, and fields
 * have many types. The first element in a field
 * is the name of the field, while the second is
 * the value of the field
 *
 * Monster is just a record type that stores its fields
 * as a list of fields. Contents are retrived via getter
 * functions
 */;
type field =
  | Text(string, string)
  | LongText(string, string)
  | Image(string, string)
and t = {fields: list(field)};

let create = (fields: list(field)) => {fields: fields};

let getField = (name, monster) =>
  monster.fields
  |. Belt.List.getBy(field =>
       switch (field) {
       | Text(fieldName, _)
       | LongText(fieldName, _)
       | Image(fieldName, _) => name == fieldName
       }
     );

let getAllFields = monster => monster.fields;