open Jest;
open Expect;

test("toBe", () =>
  expect(1 + 2) |> toBe(3)
);