import type { ItemId } from "../App";

export function Item({ id, text, handleClick }: { id: ItemId, text: string, handleClick: () => void }) {
    return (
        <li key={id}>
            <span className="item-text">{text}</span>
            <button
                className="remove-btn"
                onClick={handleClick}
                aria-label={`Eliminar ${text}`}
            >
                Eliminar
            </button>
        </li>
    )
}