type field = {
  id: int,
  order: int,
  name: string,
  value: string,
};

type monster = {
  order: int,
  fields: list(field),
};

type monsterRecord('a) = {
  ..
  id: int
} as 'a;

/**
 * Retreive all monsters in the store
 */
let getAllMonsters: unit => list({. id: int, monster});

/**
 * Given an ID, retrieve a monster from the store
 */
let getMonster: (~id: int) => {. id: int, monster};

/**
 * Given a Monster's ID and the name of it's field, retrieve all the information about the field
 */
let getMonsterField: (~id: int, ~fieldName: string) => field;

/**
 * Adds a Monster to the store
 */
let addMonster: monster => monsterRecord({. id: int, monster});

/**
 * Given a monster's ID, update the monster with the given fields
 */
let updateMonster: (~id: int, monster) => {. id: int, monster};

/**
 * Given a monster's ID, remove it from the list
 */
let removeMonster: (~id: int) => unit;