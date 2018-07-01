/**
 * Implement the backend using LocalStorage and JSON.
 * Uses the library `bs-json` to handle encoding and
 * serialization.
 */

/**
 * In this implementation, the type is represented by an ID,
 * which is it's name
 */
type t = {name: string};

type data = Js.Json.t;

/**
 * Convert the data to a format that can be stored in localStorage
 */
let save = (data: data, backend: t) => {
  let stringifiedData = Js.Json.stringify(data);
  Dom.Storage.(localStorage |> setItem(backend.name, stringifiedData));
};

/**
 * Retrieve data from localStorage and format it as the data type
 */
let retrieve = (backend: t) => {
  let retrieved = Dom.Storage.(localStorage |> getItem(backend.name));
  switch (retrieved) {
  | Some(jsonString) => Json.parse(jsonString)
  | _ => None
  };
};

let make = (name: string) => {name: name};