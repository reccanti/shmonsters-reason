/**
 * This handles the backend, from which the User can
 * save and retieve data. The User shouldn't know anything
 * about the internals of this module
 */

/**
 * A generic type for the backend. Holds metadata
 */
type t;

/**
 * A generic type that specifies what type of data we want to
 * store in the backend, and what we want to convert it to when we
 * retrieve it
 */
type data;

/**
 * A function that retrieves all data from the backend and
 * returns it as data
 */
let retrieve: t => option(data);

/**
 * A function that saves the given data in the backend
 */
let save: (data, t) => unit;

/**
 * Makes a generic backend type 
 */
let make: (string) => t;
