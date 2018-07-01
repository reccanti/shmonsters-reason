/**
 * A module that lets the User store and manage data
 */

/**
 * The fields that describe a record that will be held in the store
 */
type id;
type content('a);
type record('a) = (id, content('a));

/**
 * A type that refers to a store
 */
type store;

/**
 * Inititalize a store with a backend
 */
let make: Backend.t => store;

/**
 * A function that retrieves all records from the store
 */
let getAllAsList: store => list(record('a));

/**
 * Create a new record in the store
 */
let add: (content('a), store) => store;

/**
 * Retrieves the contents of a record in the store with a given id
 */
let get: (id, store) => content('a);

/**
 * Update the data in the store with the given id
 */
let set: (id, content('a), store) => store;

/**
 * Delete the data from the store specified by the id
 */
let delete: (id, store) => store;