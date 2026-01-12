import { describe, expect, test } from "vitest"
import { renderHook, act } from "@testing-library/react"
import { useItems } from "../src/hooks/useItems"

describe("useItems hook", () => {
    test("should add and remove items correctly", () => {

        const { result } = renderHook(() => useItems())
        expect(result.current.items).toEqual([])

        act(() => {
            result.current.addItem("First Item")
            result.current.addItem("Second Item")
        })
        expect(result.current.items.length).toBe(2)

        act(() => {
            result.current.removeItem(result.current.items[0].id)
        })
        expect(result.current.items.length).toBe(1)
    })
})