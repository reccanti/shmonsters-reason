type field = {
  id: int,
  order: int,
  name: string,
  value: string,
};

type monster = {
  id: int,
  order: int,
  fields: list(field),
};

/**
 * Retreive all monsters in the store
 */
let getAllMonsters: unit => list(monster);

/**
 * Given an ID, retrieve a monster from the store
 */
let getMonster: (~id: int) => monster;

/**
 * Given a Monster's ID and the name of it's field, retrieve all the information about the field
 */
let getMonsterField: (~id: int, ~fieldName: string) => field;

/**
 * Adds a Monster to the store
 */
let addMonster: monster => monster;

/**
 * Given a monster's ID, update the monster with the given fields
 */
let updateMonster: (~id: int, monster) => monster;

/**
 * Given a monster's ID, remove it from the list
 */
let removeMonster: (~id: int) => unit;