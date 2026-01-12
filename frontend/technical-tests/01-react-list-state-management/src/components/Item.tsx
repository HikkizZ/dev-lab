export function Item({ text, handleClick }: { text: string, handleClick: () => void }) {
    return (
        <li>
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