import { useState } from "react"
import { type Item, type ItemId } from "../App"

export const useItems = () => {
    const [items, setItems] = useState<Item[]>([])

    const addItem = (text: string) => {
        const newItem: Item = {
            id: crypto.randomUUID(),
            timestamp: Date.now(),
            text,
        }

        setItems((prevItems) => {
            return [...prevItems, newItem]
        })
    }

    const removeItem = (id: ItemId) => {
        setItems((prevItems) => {
            return prevItems.filter((item) => item.id !== id)
        })
    }

    return { items, addItem, removeItem }
}